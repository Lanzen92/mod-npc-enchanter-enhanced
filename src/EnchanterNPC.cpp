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

namespace
{
    //Used for sorting the list.
    struct EnchantDisplayData
    {
        const EnchantDefinition* enchant;
        EnchantValidationResult validation;
        uint32 price;
    };

    // Sort with TupleProfiles. (As the standard if/else sorting had problems with the locked-flag.)
    // If locked, sort by phase Ascending
    // If unlocked, sort by phase Descending, Tier Desc, Price Desc and fallback by name.
    bool SortEnchants(const EnchantDisplayData& a, const EnchantDisplayData& b)
    {
        // Must use signed integers (int64_t) to safely hold negative values
        int64_t phaseSortA = a.validation.isLocked ? static_cast<int64_t>(a.enchant->phase) : -static_cast<int64_t>(a.enchant->phase);
        int64_t phaseSortB = b.validation.isLocked ? static_cast<int64_t>(b.enchant->phase) : -static_cast<int64_t>(b.enchant->phase);

        auto profileA = std::make_tuple(
            a.validation.isLocked,
            phaseSortA,
            -static_cast<int64_t>(a.enchant->tier),
            -static_cast<int64_t>(a.price),
            a.enchant->name
        );

        auto profileB = std::make_tuple(
            b.validation.isLocked,
            phaseSortB,
            -static_cast<int64_t>(b.enchant->tier),
            -static_cast<int64_t>(b.price),
            b.enchant->name
        );

        return profileA < profileB;
    }

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

            //LOG_INFO("server.loading", "DEBUG: Sending Gossip (NPCEnchanterID) Text ID: {}", NPCEnchanterID);
            SendGossipMenuFor(player, NPCEnchanterID, creature->GetGUID());
            return true;
        }

        //Show Subcategories and enchants
        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
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
                                if (!ValidationHelper::ValidateSubCategoryRequirements(player, subCat, lockReason))
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

                // Calculate current page (Sender 5000 = Page 0, 5001 = Page 1, etc.)
                uint32 currentPage = (sender >= 5000) ? (sender - 5000) : 0;

                for (const auto& cat : sEnchantManager->GetEnchantDatabase())
                {
                    for (const auto& subCat : cat.subTypes)
                    {
                        if (subCat.enchantCategorySubTypeId == subCategoryId)
                        {
                            constexpr uint32 MAX_ITEMS_PER_PAGE = 25;
                            //Evaluate enchants.
                            std::vector<EnchantDisplayData> displayEnchants;
                            for (const auto &enchant : subCat.enchants)
                            {
                                uint32 enchantCost = sEnchantManager->GetOrCacheEnchantPrice(player, &enchant, subCategoryId);
                                EnchantValidationResult validationResult = ValidationHelper::EvaluateEnchant(player, subCategoryId, enchant, enchantCost, currentPhase);

                                if (!validationResult.showEnchant)
                                    continue;

                                displayEnchants.push_back({ &enchant, std::move(validationResult), enchantCost });
                            }

                            //Sort list before creating gossip options.
                            std::ranges::stable_sort(displayEnchants, SortEnchants);

                            parentCategoryId = cat.enchantCategoryId;

                            //Pagination vars
                            uint32 visibleItemIndex = 0;
                            uint32 addedCount = 0;
                            bool hasNextPage = false;
                            uint32 startItem = currentPage * MAX_ITEMS_PER_PAGE;

                            for (const auto& displayData : displayEnchants)
                            {
                                // Extract variables from our struct
                                const auto& enchant = *(displayData.enchant);
                                const auto& validation = displayData.validation;
                                const auto& enchantCost = displayData.price;

                                // Pagination: Skip enchants that belong to previous pages
                                if (visibleItemIndex < startItem)
                                {
                                    visibleItemIndex++;
                                    continue;
                                }

                                // Pagination: Limit hit, break.
                                if (addedCount >= MAX_ITEMS_PER_PAGE)
                                {
                                    hasNextPage = true;
                                    break;
                                }

                                uint32 confirmAction = 500000 + (subCategoryId * 10000) + enchant.enchantId;
                                std::string label;

                                if (validation.isLocked)
                                {
                                    label = "  |cff808080" + enchant.name + " — " + validation.reason + "|r";

                                    // Using a unique ID to prevent client UI grouping bugs
                                    AddGossipItemFor(player, GOSSIP_ICON_VENDOR, label, GOSSIP_SENDER_MAIN, 9900000 + enchant.enchantId);
                                }
                                else
                                {
                                    label = "  " + enchant.name + validation.priceString;
                                    std::string popupMessage =  "Are you entirely certain your gear can handle this much raw power, " + std::string(player->GetName()) +"?\n\n"
                                                                "Enchant: " + enchant.name + "\n"
                                                                "Effect: " + (enchant.description.empty() ? "None" : enchant.description) + "\n\n"
                                                                "Price calculated via highly complex, entirely made-up arcane metrics. Totaled below:";

                                    uint32 copperCost = GOLD(enchantCost);

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

                                visibleItemIndex++;
                                addedCount++;
                            }

                            // GossipOptions for next / pref page.
                            if (currentPage > 0)
                            {
                                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "  <- Previous Page", 5000 + currentPage - 1, action);
                            }
                            if (hasNextPage)
                            {
                                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "  Next Page ->", 5000 + currentPage + 1, action);
                            }

                            break;
                        }
                    }
                }

                if (parentCategoryId != 0)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_TALK, "  <- Back to Categories", GOSSIP_SENDER_MAIN, 10000 + parentCategoryId);
                }
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
            //EnchantID not found. Something went really wrong in the gossip menu.
            if (!enchant->enchantId)
            {
                //Todo fix this line..
                ChatHandler(player->GetSession()).SendSysMessage("Something went wrong.. Sorry!");
                player->PlayerTalkClass->SendCloseGossip();
                creature->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
                return;
            }
            //Check if gold should be removed.
            if (!NPCEnchanterEnhancedFreeEnchants || NPCEnchanterEnhancedDynamicPricesOnEnchants)
            {
                // This has been verified already, but one last gold check.
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
}

void AddSC_NPCEnchanterEnhanced()
{
    new NPCEnchanterEnhanced();
    new NPCEnchanterEnhancedAnnouncer();
}
