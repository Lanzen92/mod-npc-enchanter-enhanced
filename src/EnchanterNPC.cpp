/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

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

    //Show Categories.
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
        LOG_INFO("server.loading", "DEBUG: Sending Gossip (NPCEnchanterID) Text ID: {}", NPCEnchanterID);
        SendGossipMenuFor(player, NPCEnchanterID, creature->GetGUID());
        return true;
    }

    //Show Subcategories and enchants
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        if (!NPCEnchanterEnhancedEnabled)
            return false;

        uint32 currentPhase;
        if (NPCEnchanterEnhancedIndividualProgression)
            currentPhase = GetPlayerPhase(player);
        else
            currentPhase = NPCEnchanterEnhancedPhase;

        ClearGossipMenuFor(player);

        // Handling Dummy / Locked Option Refresh (Actions 99900 - 99999)
        if (action >= 99900 && action < 100000)
        {
            uint32 subCategoryId = action - 99900;
            uint32 parentCategoryId = 0;

            for (const auto& cat : sEnchantManager->GetEnchantDatabase())
            {
                for (const auto& subCat : cat.subTypes)
                {
                    if (subCat.enchantCategorySubTypeId == subCategoryId)
                    {
                        parentCategoryId = cat.enchantCategoryId;
                        break;
                    }
                }
                if (parentCategoryId != 0)
                    break;
            }

            // Retrigger the subcategory view.
            if (parentCategoryId != 0)
            {
                return OnGossipSelect(player, creature, GOSSIP_SENDER_MAIN, 10000 + parentCategoryId);
            }

            return OnGossipHello(player, creature);
        }

        //Back to Main Menu
        if (action == 99999)
        {
            return OnGossipHello(player, creature);
        }

        // 1. Display SubCategories (Actions 10000-19999)
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
                            //Check if all enchants in the subCategory needs a specific profession and skill
                            //If the player not got the right skill for any of them, disable the subCategory
                            if (!ValidationHelper::ValidateSubCategoryProfession(player, subCat, lockReason))
                            {
                                isLocked = true;
                            }
                        }

                        if (!isLocked)
                        {
                            //Check if the player got an item equipped for the subCategory.
                            if (!ValidationHelper::ValidateSubCategoryEquipment(player, subCat.enchantCategorySubTypeId, lockReason))
                            {
                                isLocked = true;
                            }
                        }

                        uint32 gossipAction = 20000 + subCat.enchantCategorySubTypeId;
                        std::string label;

                        if (isLocked)
                        {
                            label = "|TInterface/ICONS/" + subCat.icon + ":24:24:-18|t|cff808080" + subCat.name + lockReason + "|r";
                            gossipAction = 99900 + subCat.enchantCategorySubTypeId;
                        }
                        else
                        {
                            label = "|TInterface/ICONS/" + subCat.icon + ":24:24:-18|t" + subCat.name;
                        }

                        AddGossipItemFor(player, 1, label, GOSSIP_SENDER_MAIN, gossipAction);
                    }
                    break;
                }
            }

            AddGossipItemFor(player, GOSSIP_ICON_TALK, "  <- Back to Main Menu", GOSSIP_SENDER_MAIN, 99999);
            //LOG_INFO("server.loading", "DEBUG: Sending Gossip (NPCEnchanterID + 1) Text ID: {}", NPCEnchanterID + 1);
            SendGossipMenuFor(player, NPCEnchanterID + 1, creature->GetGUID());
            return true;
        }

        // 2. Display Enchants (Actions 20000-29999)
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
                            uint32 enchantCost = sEnchantManager->GetOrCacheEnchantPrice(player, &enchant, subCategoryId);
                            EnchantValidationResult validation = ValidationHelper::EvaluateEnchant(player, subCategoryId, enchant, enchantCost, currentPhase);

                            // Directly point to the execution action range (e.g., 500000+)
                            uint32 confirmAction = 500000 + (subCategoryId * 10000) + enchant.enchantId;

                            if (validation.showEnchant)
                            {
                                std::string label;
                                if (validation.isLocked)
                                {
                                    label = "  |cff808080" + enchant.name + " — " + validation.reason + "|r";
                                    // Locked items keep a safe dummy action or can bypass popup
                                    AddGossipItemFor(player, GOSSIP_ICON_VENDOR, label, GOSSIP_SENDER_MAIN, 99900 + subCategoryId);
                                }
                                else
                                {
                                    label = "  " + enchant.name + validation.priceString;
                                    std::string popupMessage =  "Are you entirely certain your gear can handle this much raw power, " + std::string(player->GetName()) +"?\n\n"
                                                                "Enchant: " + enchant.name + "\n"
                                                                "Effect: " + (enchant.description.empty() ? "None" : enchant.description) + "\n\n"
                                                                "Price calculated via highly complex, entirely made-up arcane metrics. Totaled below:";

                                    uint32 copperCost = GOLD(enchantCost);

                                    // Add item with the native popup and money display attached!
                                    AddGossipItemFor(
                                        player,
                                        GOSSIP_ICON_VENDOR,
                                        label,
                                        GOSSIP_SENDER_MAIN,
                                        confirmAction,
                                        popupMessage,
                                        static_cast<uint32>(copperCost),
                                        false
                                    );
                                }
                            }
                        }
                        break;
                    }
                }
            }

            AddGossipItemFor(player, GOSSIP_ICON_TALK, "  <- Back to Categories", GOSSIP_SENDER_MAIN, 10000 + parentCategoryId);
            SendGossipMenuFor(player, NPCEnchanterID + 2, creature->GetGUID());
            return true;
        }

        // Handling the actual enchanting (Actions >= 500000)
        if (action >= 500000 && action < 900000)
        {
            uint32 owningSubCategoryId = (action - 500000) / 10000;
            uint32 enchantId = (action - 500000) % 10000;

            const EnchantDefinition* selectedEnchant = sEnchantManager->GetEnchantDefinition(enchantId);
            if (!selectedEnchant)
            {
                return true;
            }

            uint8 slot = GetEquipmentSlotFromSubCategory(owningSubCategoryId);
            Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);

            Enchant(player, creature, targetItem, selectedEnchant, owningSubCategoryId);
            return true;
        }

        return true;
    }

    //Enchant the item
    static void Enchant(Player* player, Creature* creature, Item* item, const EnchantDefinition* enchant, uint32 subCatId)
    {
        //This should already been verified, but one last check.
        if (!item)
        {
            creature->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
            creature->Whisper("Please equip the item you would like to enchant!", LANG_UNIVERSAL, player);
            player->CastSpell(player, 12512);
            player->PlayerTalkClass->SendCloseGossip();
            return;
        }
        //EnchantID now found.. Something went really wrong in the gossip menu.
        if (!enchant->enchantId)
        {
            //Todo fix this line..
            //LOG_ERROR("server.loading", "[NPCEnchanterEnhanced] Error when enchanting. EnchantId not found. PlayerGUID: {} Item: {}", player->GetGUID(), item->GetGUID(), item->GetTemplate()->Name1 );
            ChatHandler(player->GetSession()).SendSysMessage("Something went wrong.. Sorry!");
            player->PlayerTalkClass->SendCloseGossip();
            creature->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
            return;
        }
        //Check if gold should be removed.
        if (!NPCEnchanterEnhancedFreeEnchants || NPCEnchanterEnhancedDynamicPricesOnEnchants)
        {
            // This has been verifed already, but one last gold check.
            uint32 costInCopper = GOLD(sEnchantManager->GetOrCacheEnchantPrice(player, enchant, subCatId));
            if (player->GetMoney() < costInCopper)
            {
                creature->Whisper("Are you trying to fool me?! You dont have enough gold for this!", LANG_UNIVERSAL, player);
                return;
            }

            player->ModifyMoney(-static_cast<int32>(costInCopper));
        }

        //Enchant the item!
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
