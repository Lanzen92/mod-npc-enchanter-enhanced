
#include <vector>

#include "Cell.h"
#include "CellImpl.h"
#include "Chat.h"
#include "CombatAI.h"
#include "Configuration/Config.h"
#include "DBCStores.h"
#include "DBCStructure.h"
#include "GameEventMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "GameObject.h"
#include "InstanceScript.h"
#include "ObjectMgr.h"
#include "PassiveAI.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Unit.h"
#include "ConfigManager.h"
#include "EnchantManager.h"

class NPCEnchanterEnhancedAnnouncer : public PlayerScript {

    public:

    NPCEnchanterEnhancedAnnouncer() : PlayerScript("NPCEnchanterEnhancedAnnouncer", {
        PLAYERHOOK_ON_LOGIN
    }) {}

    void OnPlayerLogin(Player* player) {
        if (NPCEnchanterEnhancedAnnounce)
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the NPCEnchanterEnhanced module.");
    }
};


class NPCEnchanterEnhanced : public CreatureScript {
    public:
    NPCEnchanterEnhanced() : CreatureScript("NPCEnchanterEnhanced") {
    }

    bool OnGossipHello(Player* player, Creature* creature) override {

        if (!NPCEnchanterEnhancedEnabled)
            return false;

        ClearGossipMenuFor(player);

        for (const auto& category : sEnchantManager->GetEnchantDatabase())
        {
            uint32 action = 10000 + category.enchantCategoryId;
            std::string label = "|TInterface/ICONS/" + category.icon + ":24:24:-18|t" + category.name;
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, label, GOSSIP_SENDER_MAIN, action);
        }

        SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        if (!NPCEnchanterEnhancedEnabled)
            return false;

        ClearGossipMenuFor(player);

        // 1. Handling Category (Actions 10000-19999)
        if (action >= 10000 && action < 20000)
        {
            uint32 categoryId = action - 10000;
            for (const auto& cat : sEnchantManager->GetEnchantDatabase())
            {
                if (cat.enchantCategoryId == categoryId)
                {
                    for (const auto& subCat : cat.subTypes)
                    {
                        bool isLocked = false;
                        std::string lockReason = "";

                        // LOG_INFO("server.loading", "Evaluating SubCat: ID = {}, Name = {}, ProfReq = '{}', SkillReq = {}, Player HasSkill: {}, SkillVal: {}",
                        //    subCat.enchantCategorySubTypeId, subCat.name, subCat.professionRequirement, subCat.professionSkillRequirement,
                        //    player->HasSkill(GetSkillTypeFromString(subCat.professionRequirement)),
                        //    player->GetSkillValue(GetSkillTypeFromString(subCat.professionRequirement)));

                        if (NPCEnchanterEnhancedLockProfessionEnchants && !subCat.professionRequirement.empty())
                        {
                            SkillType reqSkill = GetSkillTypeFromString(subCat.professionRequirement);
                            if (reqSkill != SKILL_NONE)
                            {
                                if (!player->HasSkill(reqSkill) || player->GetSkillValue(reqSkill) < subCat.professionSkillRequirement)
                                {
                                    isLocked = true;
                                    lockReason = " (Requires " + subCat.professionRequirement + " " + std::to_string(subCat.professionSkillRequirement) + ")";
                                }
                            }
                        }

                        uint32 subAction = 20000 + subCat.enchantCategorySubTypeId;
                        std::string label;

                        if (isLocked)
                        {
                            label = "|TInterface/ICONS/" + subCat.icon + ":24:24:-18|t|cff808080" + subCat.name + lockReason + "|r";
                            subAction = 99998; // Dummy action
                        }
                        else
                        {
                            label = "|TInterface/ICONS/" + subCat.icon + ":24:24:-18|t" + subCat.name;
                        }

                        AddGossipItemFor(player, GOSSIP_ICON_CHAT, label, GOSSIP_SENDER_MAIN, subAction);
                    }
                    break;
                }
            }

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "<- Back to Main Menu", GOSSIP_SENDER_MAIN, 99999);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
        }

        // 2. Handling CategorySubType (Actions 20000-29999)
        if (action >= 20000 && action < 30000)
        {
            uint32 subCategoryId = action - 20000;
            uint32 parentCategoryId = 0;

            for (const auto& cat : sEnchantManager->GetEnchantDatabase())
            {
                for (const auto& subCat : cat.subTypes)
                {
                    if (subCat.enchantCategorySubTypeId == subCategoryId)
                    {
                        parentCategoryId = cat.enchantCategoryId;
                        for (const auto& enchant : subCat.enchants)
                        {
                            AddGossipItemFor(player, GOSSIP_ICON_BATTLE, enchant.name, GOSSIP_SENDER_MAIN, enchant.enchantId);
                        }
                        break;
                    }
                }
            }

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "<- Back to Categories", GOSSIP_SENDER_MAIN, 10000 + parentCategoryId);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
        }

        // 3. Back to Main Menu
        if (action == 99999)
        {
            return OnGossipHello(player, creature);
        }

        // 4. Dummy
        if (action == 99998)
        {
            return true;
        }


        // 4. Handling Clicked Enchant
        const EnchantDefinition* selectedEnchant = sEnchantManager->GetEnchantDefinition(action);
        if (!selectedEnchant)
        {
            // Fallback
            return true;
        }

        uint32 owningSubCategoryId = 0;
        for (const auto& cat : sEnchantManager->GetEnchantDatabase())
        {
            for (const auto& subCat : cat.subTypes)
            {
                for (const auto& enchant : subCat.enchants)
                {
                    if (enchant.enchantId == selectedEnchant->enchantId)
                    {
                        owningSubCategoryId = subCat.enchantCategorySubTypeId;
                        break;
                    }
                }
            }
        }

        //Enchantlogic here..

        // Re-display the enchantment
        for (const auto& cat : sEnchantManager->GetEnchantDatabase())
        {
            for (const auto& subCat : cat.subTypes)
            {
                if (subCat.enchantCategorySubTypeId == owningSubCategoryId)
                {
                    for (const auto& enchant : subCat.enchants)
                    {
                        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, enchant.name, GOSSIP_SENDER_MAIN, enchant.enchantId);
                    }
                    break;
                }
            }
        }

        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "<- Back to Subcategories", GOSSIP_SENDER_MAIN, 20000 + owningSubCategoryId);
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }


    SkillType static GetSkillTypeFromString(const std::string& profName)
    {
        if (profName == "Enchanting")   return SKILL_ENCHANTING;
        if (profName == "Engineering")  return SKILL_ENGINEERING;
        if (profName == "Blacksmithing") return SKILL_BLACKSMITHING;
        if (profName == "Tailoring")    return SKILL_TAILORING;
        if (profName == "Leatherworking") return SKILL_LEATHERWORKING;
        if (profName == "Alchemy")      return SKILL_ALCHEMY;
        if (profName == "Herbalism")    return SKILL_HERBALISM;
        if (profName == "Mining")       return SKILL_MINING;
        if (profName == "Skinning")     return SKILL_SKINNING;
        if (profName == "Inscription")  return SKILL_INSCRIPTION;
        if (profName == "Jewelcrafting") return SKILL_JEWELCRAFTING;

        return SKILL_NONE;
    }

};

void AddSC_NPCEnchanterEnhanced()
{
    new NPCEnchanterEnhancedAnnouncer();
    new NPCEnchanterEnhanced();
}
