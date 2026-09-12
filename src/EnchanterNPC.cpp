
#include <vector>


#include "Chat.h"
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
#include "helper.h"

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

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        if (!NPCEnchanterEnhancedEnabled)
            return false;

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

                        if (NPCEnchanterEnhancedLockProfessionEnchants)
                        {
                            lockReason = sEnchantManager->GetProfessionLockedPhrase(subCat.enchantCategorySubTypeId);
                            if (!lockReason.empty())
                            {
                                for (const auto& enchant : subCat.enchants)
                                {
                                    if (!enchant.professionRequirement.empty())
                                    {
                                        SkillType reqSkill = GetProfessionSkillTypeFromString(enchant.professionRequirement);
                                        if (reqSkill != SKILL_NONE)
                                        {
                                            if (!player->HasSkill(reqSkill) || player->GetSkillValue(reqSkill) < enchant.professionSkillRequirement)
                                            {
                                                isLocked = true;
                                                break;
                                            }
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
                            bool isEnchantLocked = false;
                            std::string enchantLockReason = "";
                            std::string priceString = "";

                            //Todo
                            //Check Phases
                            //Check levelRequirement
                            //Check itemLevelRequirements
                            //Check if correct weapon for enchant (Now we can applie 2H on 1H etc)

                            //Check for profession requirements
                            if (NPCEnchanterEnhancedLockProfessionEnchants && !enchant.professionRequirement.empty())
                            {
                                SkillType reqSkill = GetProfessionSkillTypeFromString(enchant.professionRequirement);
                                if (reqSkill != SKILL_NONE)
                                {
                                    if (!player->HasSkill(reqSkill) || player->GetSkillValue(reqSkill) < enchant.professionSkillRequirement)
                                    {
                                        isEnchantLocked = true;
                                        enchantLockReason = " (Requires " + std::to_string(enchant.professionSkillRequirement) + " " + enchant.professionRequirement + ")";
                                    }
                                }
                            }

                            //If enabled, add gold costs.
                            if (!NPCEnchanterEnhancedFreeEnchants || NPCEnchanterEnhancedDynamicPricesOnEnchants)
                            {
                                priceString = enchant.cost > 0 ? "   |cffffd700(" + std::to_string(enchant.cost) + "g)|r" : "";
                                uint64 totalCostCopper = GOLD(enchant.cost);
                                if (player->GetMoney() < totalCostCopper)
                                {
                                    isEnchantLocked = true;
                                    enchantLockReason = " (Not enough gold)";
                                }
                            }

                            uint32 gossipAction = (subCategoryId << 16) | (enchant.enchantId & 0xFFFF);
                            std::string label;

                            if (isEnchantLocked)
                            {
                                label = "|cff808080" + enchant.name + enchantLockReason + "|r";
                                gossipAction = 99998; // Dummy action
                            }
                            else
                            {
                                label = enchant.name + priceString;
                            }

                            AddGossipItemFor(player, GOSSIP_ICON_BATTLE, label, GOSSIP_SENDER_MAIN, gossipAction);
                        }
                        break;
                    }
                }
            }

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "<- Back to Categories", GOSSIP_SENDER_MAIN, 10000 + parentCategoryId);
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

            LOG_INFO("server.loading", "Resolved SubCat {} to Equipment Slot {}. Item found: {}",
                owningSubCategoryId, slot, targetItem ? targetItem->GetTemplate()->Name1.c_str() : "nullptr");

            Enchant(player, creature, targetItem, selectedEnchant);
            return true;
        }

        return true;
    }


    void Enchant(Player* player, Creature* creature, Item* item, const EnchantDefinition* enchant)
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
            uint64 costInCopper = GetEnchantPriceInCopper(enchant);
            if (player->GetMoney() < costInCopper)
            {
                creature->Whisper("You do not have enough gold for this enchantment!", LANG_UNIVERSAL, player);
                return;
            }

            player->ModifyMoney(-(int64)costInCopper);
        }

        item->ClearEnchantment(PERM_ENCHANTMENT_SLOT);
        item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchant->enchantId, 0, 0);

        creature->CastSpell(player, 12512);
        player->PlayerTalkClass->SendCloseGossip();
    }

    //Move to helper
    SkillType static GetProfessionSkillTypeFromString(const std::string& profName)
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
    //Move to helper
    EquipmentSlots static GetEquipmentSlotFromSubCategory(uint32 subCat)
    {
        switch (subCat)
        {
            case EnchantSubCategory::Weapon_1H_Melee:
            case EnchantSubCategory::Weapon_1H_Caster:
            case EnchantSubCategory::Weapon_2H_Melee:
            case EnchantSubCategory::Weapon_2H_Caster:
                return EquipmentSlots::EQUIPMENT_SLOT_MAINHAND;

            case EnchantSubCategory::Weapon_1H_Melee_Offhand:
                return EquipmentSlots::EQUIPMENT_SLOT_OFFHAND;

            case EnchantSubCategory::Weapon_Ranged:
                return EquipmentSlots::EQUIPMENT_SLOT_RANGED;

            case EnchantSubCategory::Subtype_Shield:
                return EquipmentSlots::EQUIPMENT_SLOT_OFFHAND;

            case EnchantSubCategory::Armor_Helm:
                return EquipmentSlots::EQUIPMENT_SLOT_HEAD;
            case EnchantSubCategory::Armor_Shoulders:
                return EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS;
            case EnchantSubCategory::Armor_Cloak:
                return EquipmentSlots::EQUIPMENT_SLOT_BACK;
            case EnchantSubCategory::Armor_Chest:
                return EquipmentSlots::EQUIPMENT_SLOT_CHEST;
            case EnchantSubCategory::Armor_Waist:
                return EquipmentSlots::EQUIPMENT_SLOT_WAIST;
            case EnchantSubCategory::Armor_Bracers:
                return EquipmentSlots::EQUIPMENT_SLOT_WRISTS;
            case EnchantSubCategory::Armor_Gloves:
                return EquipmentSlots::EQUIPMENT_SLOT_HANDS;
            case EnchantSubCategory::Armor_Legs:
                return EquipmentSlots::EQUIPMENT_SLOT_LEGS;
            case EnchantSubCategory::Armor_Boots:
                return EquipmentSlots::EQUIPMENT_SLOT_FEET;
            case EnchantSubCategory::Armor_Ring_Slot1:
                return EquipmentSlots::EQUIPMENT_SLOT_FINGER1;
            case EnchantSubCategory::Armor_Ring_Slot2:
                return EquipmentSlots::EQUIPMENT_SLOT_FINGER2;

            default:
                return EquipmentSlots::EQUIPMENT_SLOT_MAINHAND;
        }
    }
};

void AddSC_NPCEnchanterEnhanced()
{
    new NPCEnchanterEnhancedAnnouncer();
    new NPCEnchanterEnhanced();
}
