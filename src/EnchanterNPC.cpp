#include <vector>

#include "Chat.h"
#include "CommonHelper.h"
#include "GameEventMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Unit.h"
#include "ConfigManager.h"
#include "EnchantManager.h"
#include "PriceHelper.h"
#include "ValidationHelper.h"

class NPCEnchanterEnhancedAnnouncer : public PlayerScript {

    public:

    NPCEnchanterEnhancedAnnouncer() : PlayerScript("NPCEnchanterEnhancedAnnouncer", {
        PLAYERHOOK_ON_LOGIN
    }) {}

    void OnPlayerLogin(Player* player) override {
        if (NPCEnchanterEnhancedAnnounce)
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00NPCEnchanterEnhanced |rmodule.");
    }
};

class NPCEnchanterEnhanced : public CreatureScript {
    public:
    NPCEnchanterEnhanced() : CreatureScript("NPCEnchanterEnhanced") {
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {

        if (!NPCEnchanterEnhancedEnabled)
            return false;

        ClearGossipMenuFor(player);

        for (const auto& category : sEnchantManager->GetEnchantDatabase())
        {
            uint32 action = 10000 + category.enchantCategoryId;
            std::string label = "|TInterface/ICONS/" + category.icon + ":24:24:-18|t  " + category.name;
            AddGossipItemFor(player, 1, label, GOSSIP_SENDER_MAIN, action);
        }

        SendGossipMenuFor(player, NPCEnchanterID, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        if (!NPCEnchanterEnhancedEnabled)
            return false;

        uint32 currentPhase;
        if (NPCEnchanterEnhancedIndividualProgression)
            currentPhase = ValidationHelper::GetPlayerPhase(player);
        else
            currentPhase = NPCEnchanterEnhancedPhase;

        ClearGossipMenuFor(player);

        //Back to Main Menu
        if (action == 99999)
        {
            return OnGossipHello(player, creature);
        }

        //Dummy (When pressing disabled options etc)
        if (action == 99998)
        {
            return true;
        }

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

                        //If no enchants, skip this subcategory
                        if (sEnchantManager->SubCategoryHasNoEnchants(subCat.enchantCategorySubTypeId))
                        {
                            continue;
                        }

                        if (!NPCEnchanterEnhancedIgnoreProfessionRequirements)
                        {
                            lockReason = sEnchantManager->GetProfessionLockedPhrase(subCat.enchantCategorySubTypeId);
                            if (!lockReason.empty())
                            {
                                // If the subcategory requires professions across the board,
                                // you can evaluate your conditions smoothly:
                                for (const auto& enchant : subCat.enchants)
                                {
                                    if (!enchant.professionRequirement.empty())
                                    {
                                        SkillType reqSkill = GetProfessionSkillTypeFromString(enchant.professionRequirement);
                                        if (reqSkill != SKILL_NONE && (!player->HasSkill(reqSkill) || player->GetSkillValue(reqSkill) < enchant.professionSkillRequirement))
                                        {
                                            isLocked = true;
                                            break;
                                        }
                                    }
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

                        AddGossipItemFor(player, 1, label, GOSSIP_SENDER_MAIN, subAction);
                    }
                    break;
                }
            }

            AddGossipItemFor(player, GOSSIP_ICON_TALK, "  <- Back to Main Menu", GOSSIP_SENDER_MAIN, 99999);
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
                            EnchantValidationResult validation = ValidationHelper::EvaluateEnchant(player, subCategoryId, enchant, currentPhase);

                            LOG_INFO("server.loading", "validation show enchant {}, validation islocked {}, validation reason {}, validation price {}",
                                validation.showEnchant, validation.isLocked, validation.reason, validation.priceString);

                            uint32 gossipAction = (subCategoryId << 16) | (enchant.enchantId & 0xFFFF);

                            if (validation.showEnchant)
                            {
                                std::string label;
                                if (validation.isLocked)
                                {
                                    label = "  |cff808080" + enchant.name + " — " + validation.reason + "|r";
                                    gossipAction = 99998; // Dummy action
                                }
                                else
                                {
                                    label = "  " + enchant.name + validation.priceString;
                                }
                                AddGossipItemFor(player, GOSSIP_ICON_VENDOR, label, GOSSIP_SENDER_MAIN, gossipAction);
                            }
                        }
                        break;
                    }
                }
            }

            AddGossipItemFor(player, GOSSIP_ICON_TALK, "  <- Back to Categories", GOSSIP_SENDER_MAIN, 10000 + parentCategoryId);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
        }

        // 4. Handling Clicked Enchant (Packed Actions are >= 65536 since SubCat is shifted left by 16)
        if (action >= 65536)
        {
            uint32 owningSubCategoryId = action >> 16;
            uint32 enchantId = action & 0xFFFF;

            const EnchantDefinition* selectedEnchant = sEnchantManager->GetEnchantDefinition(enchantId);
            if (!selectedEnchant)
            {
                return true;
            }

            uint8 slot = GetEquipmentSlotFromSubCategory(owningSubCategoryId);
            Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);

            Enchant(player, creature, targetItem, selectedEnchant);
            return true;
        }

        return true;
    }

    static void Enchant(Player* player, Creature* creature, Item* item, const EnchantDefinition* enchant)
    {
        if (!item)
        {
            creature->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
            creature->Whisper("Please equip the item you would like to enchant!", LANG_UNIVERSAL, player);
            player->CastSpell(player, 12512); // enchantment visual
            player->PlayerTalkClass->SendCloseGossip();
            return;
        }

        if (!enchant->enchantId)
        {
            ChatHandler(player->GetSession()).SendSysMessage("Something went wrong.. Sorry!");
            player->PlayerTalkClass->SendCloseGossip();
            creature->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
            return;
        }

        if (!NPCEnchanterEnhancedFreeEnchants || NPCEnchanterEnhancedDynamicPricesOnEnchants)
        {
            uint64 costInCopper = PriceHelper::GetEnchantPriceInCopper(enchant);
            if (player->GetMoney() < costInCopper)
            {
                creature->Whisper("You do not have enough gold for this enchant!", LANG_UNIVERSAL, player);
                return;
            }

            player->ModifyMoney(-static_cast<int64>(costInCopper));
        }

        item->ClearEnchantment(PERM_ENCHANTMENT_SLOT);
        item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchant->enchantId, 0, 0);

        creature->CastSpell(player, 12512);
        player->PlayerTalkClass->SendCloseGossip();
    }
};

void AddSC_NPCEnchanterEnhanced()
{
    new NPCEnchanterEnhancedAnnouncer();
    new NPCEnchanterEnhanced();
}
