/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

#include "EnchantManager.h"
#include <algorithm>
#include <string>

#include "CommonHelper.h"
#include "ConfigManager.h"
#include "PriceHelper.h"

NPCEnchanterEnhancedEnchantManager* NPCEnchanterEnhancedEnchantManager::instance()
{
    static NPCEnchanterEnhancedEnchantManager instance;
    return &instance;
}

NPCEnchanterEnhancedEnchantManager::NPCEnchanterEnhancedEnchantManager()
{
    m_enchantDatabase = {
        //Weapon Category
        EnchantCategoryDefinition {
            static_cast<uint32>(EnchantCategory::Weapon),
            "Weapon enchants",
            "Inv_axe_113",
            {
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_1H_Melee),
                    .name = "One-Handed Melee",
                    .icon = "inv_sword_39",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2564, "Agility", "+15 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 2563, "Strength", "+15 Strength", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 1900, "Crusader", "", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1894, "Icy Weapon", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 803,  "Fiery Weapon", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1897, "Superior Striking", "+5 Weapon Damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 25 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 864,  "Greater Striking", "+4 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 10 },
                        EnchantDefinition{ 943,  "Striking", "+3 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 241,  "Lesser Striking", "+2 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 250,  "Minor Striking", "+1 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 854,  "Lesser Elemental Slayer", "+6 Weapon Damage to Elementals", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 190,  "Lesser Beastslayer", "+6 Weapon Damage to Beasts", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 188,  "Minor Beastslayer", "+2 Weapon Damage to Beasts", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2673, "Mongoose", "Occasionally +120 Agility and +2% Attack Speed for 15 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 3225, "Executioner", "Occasionally ignores 840 of your enemy’s armor for 15 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 2675, "Battlemaster", "Occasionally heal nearby party members 180-300 health", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 11, 300 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3223, "Adamantite Weapon Chain", "50% disarm duration reduction and +15 Parry Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 50 },
                        EnchantDefinition{ 3273, "Deathfrost", "+150 Frost Damage and the target’s melee, ranged, and casting speed is decreased by 15% for 8 seconds.", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 2668, "Potency", "+20 Strength", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 3222, "Greater Agility", "+20 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 963,  "Major Striking", "+7 Weapon Damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 35 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3789, "Berserking", "Occasionally increases attack power by 400 at the cost of reduced armor", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 600 },
                        EnchantDefinition{ 3869, "Blade Ward", "Occasionally increases parry rating by 200 and inflicts 600-800 damage on your next parry", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 75, 14, 550 },
                        EnchantDefinition{ 3870, "Blood Draining", "Occasionally grant Blood Reserve, healing for 360-440 when falling below 35% health", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 75, 14, 550 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3833, "Superior Potency", "+65 Attack Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 250 },
                        EnchantDefinition{ 1606, "Greater Potency", "+50 Attack Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 },
                        EnchantDefinition{ 1103, "Exceptional Agility", "+26 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 165 },
                        EnchantDefinition{ 3788, "Accuracy", "+25 Critical Strike Rating and +25 Hit Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 200 },
                        EnchantDefinition{ 3251, "Giant Slayer", "A chance of reducing movement speed and doing additional damage against giants", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 },
                        EnchantDefinition{ 3731, "Titanium Weapon Chain", "50% disarm duration reduction and +28 Hit Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 80 },
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_1H_Melee_Offhand),
                    .name = "Offhand",
                    .icon = "inv_weapon_shortblade_03",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2564, "Agility", "+15 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 2563, "Strength", "+15 Strength", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 1900, "Crusader", "", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1894, "Icy Weapon", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 803,  "Fiery Weapon", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1897, "Superior Striking", "+5 Weapon Damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 25 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 864,  "Greater Striking", "+4 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 10 },
                        EnchantDefinition{ 943,  "Striking", "+3 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 241,  "Lesser Striking", "+2 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 250,  "Minor Striking", "+1 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 854,  "Lesser Elemental Slayer", "+6 Weapon Damage to Elementals", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 190,  "Lesser Beastslayer", "+6 Weapon Damage to Beasts", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 188,  "Minor Beastslayer", "+2 Weapon Damage to Beasts", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2673, "Mongoose", "Occasionally +120 Agility and +2% Attack Speed for 15 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 3225, "Executioner", "Occasionally ignores 840 of your enemy’s armor for 15 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 2675, "Battlemaster", "Occasionally heal nearby party members 180-300 health", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 11, 300 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3223, "Adamantite Weapon Chain", "50% disarm duration reduction and +15 Parry Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 50 },
                        EnchantDefinition{ 3273, "Deathfrost", "+150 Frost Damage and the target’s melee, ranged, and casting speed is decreased by 15% for 8 seconds.", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 2668, "Potency", "+20 Strength", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 3222, "Greater Agility", "+20 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 963,  "Major Striking", "+7 Weapon Damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 35 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3789, "Berserking", "Occasionally increases attack power by 400 at the cost of reduced armor", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 600 },
                        EnchantDefinition{ 3869, "Blade Ward", "Occasionally increases parry rating by 200 and inflicts 600-800 damage on your next parry", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 75, 14, 550 },
                        EnchantDefinition{ 3870, "Blood Draining", "Occasionally grant Blood Reserve, healing for 360-440 when falling below 35% health", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 75, 14, 550 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3833, "Superior Potency", "+65 Attack Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 250 },
                        EnchantDefinition{ 1606, "Greater Potency", "+50 Attack Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 },
                        EnchantDefinition{ 1103, "Exceptional Agility", "+26 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 165 },
                        EnchantDefinition{ 3788, "Accuracy", "+25 Critical Strike Rating and +25 Hit Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 200 },
                        EnchantDefinition{ 3251, "Giant Slayer", "A chance of reducing movement speed and doing additional damage against giants", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 },
                        EnchantDefinition{ 3731, "Titanium Weapon Chain", "50% disarm duration reduction and +28 Hit Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 80 },
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_2H_Melee),
                    .name = "Two-Handed Melee",
                    .icon = "inv_axe_09",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2646, "Agility", "+25 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 2, 200 },
                        EnchantDefinition{ 1900, "Crusader", "", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1894, "Icy Weapon", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 803,  "Fiery Weapon", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1896, "Superior Impact", "+9 Weapon Damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 15 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 963,  "Greater Impact", "+7 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 10 },
                        EnchantDefinition{ 1897, "Impact", "+5 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 943,  "Lesser Impact", "+3 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 241,  "Minor Impact", "+2 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2673, "Mongoose", "Occasionally +120 Agility and +2% Attack Speed for 15 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 3225, "Executioner", "Occasionally ignores 840 of your enemy’s armor for 15 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 2675, "Battlemaster", "Occasionally heal nearby party members 180-300 health", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 11, 300 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 2667, "Savagery", "+70 Attack Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 125 },
                        EnchantDefinition{ 2670, "Major Agility", "+35 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 125 },
                        EnchantDefinition{ 3223, "Adamantite Weapon Chain", "50% disarm duration reduction and +15 Parry Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 50 },
                        EnchantDefinition{ 3273, "Deathfrost", "+150 Frost Damage and the target’s melee, ranged, and casting speed is decreased by 15% for 8 seconds.", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 2668, "Potency", "+20 Strength", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 3222, "Greater Agility", "+20 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 963,  "Major Striking", "+7 Weapon Damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 35 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3827, "Massacre", "+110 Attack Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 600 },
                        EnchantDefinition{ 3789, "Berserking", "Occasionally increases attack power by 400 at the cost of reduced armor", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 600 },
                        EnchantDefinition{ 3869, "Blade Ward", "Occasionally increases parry rating by 200 and inflicts 600-800 damage on your next parry", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 75, 14, 550 },
                        EnchantDefinition{ 3870, "Blood Draining", "Occasionally grant Blood Reserve, healing for 360-440 when falling below 35% health", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 75, 14, 550 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3828, "Greater Savagery", "+85 Attack Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 250 },
                        EnchantDefinition{ 3247, "Scourgebane", "+140 Attack Power against Undead", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 165 },
                        EnchantDefinition{ 3833, "Superior Potency", "+65 Attack Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 250 },
                        EnchantDefinition{ 1606, "Greater Potency", "+50 Attack Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 },
                        EnchantDefinition{ 1103, "Exceptional Agility", "+26 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 165 },
                        EnchantDefinition{ 3251, "Giant Slayer", "A chance of reducing movement speed and doing additional damage against giants", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 },
                        EnchantDefinition{ 3788, "Accuracy", "+25 Critical Strike Rating and +25 Hit Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 200 },
                        EnchantDefinition{ 3731, "Titanium Weapon Chain", "50% disarm duration reduction and +28 Hit Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 80 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_1H_Caster),
                    .name = "One-Handed Caster",
                    .icon = "inv_weapon_shortblade_37",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2505, "Healing Power", "+55 Healing power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 2332, "Spell Power", "+30 Spell power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1124, "Mighty Intellect", "+22 Intellect", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 100 },
                        EnchantDefinition{ 2567, "Mighty Spirit", "+20 Spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 100 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 2443, "Winter’s Might", "+7 Frost spell power", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2674, "Spellsurge", "Occasionally restore 100 mana to all nearby party members over 10 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 300 },
                        EnchantDefinition{ 2671, "Sunfire", "+50 Arcane and Fire Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 2672, "Soulfrost", "+54 Frost and Shadow Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 2343, "Major Healing", "+81 Healing Power and +27 Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 300 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 2669, "Major Spellpower", "+40 Spell Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 125 },
                        EnchantDefinition{ 2666, "Major Intellect", "+30 Intellect", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 125 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3834, "Mighty Spellpower", "+63 Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 550 },
                        EnchantDefinition{ 3790, "Black Magic", "Damaging spells sometimes increase haste rating by 250 for 10 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 550 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3830, "Exceptional Spellpower", "+50 Spell Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 250 },
                        EnchantDefinition{ 3844, "Exceptional Spirit", "+45 Spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 165 },
                        EnchantDefinition{ 3239, "Icebreaker", "Chance to inflict 180 to 220 Fire damage on strike", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 },
                        EnchantDefinition{ 3241, "Lifeward", "Sometimes heals the wielder for 300 to 400 when striking in melee", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 },
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_2H_Caster),
                    .name = "Two-Handed Caster",
                    .icon = "inv_staff_13",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2505, "Healing Power", "+55 Healing power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 2332, "Spell Power", "+30 Spell power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1903, "Major Spirit", "+9 Spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 15 },
                        EnchantDefinition{ 1901, "Major Intellect", "+9 Intellect", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 15 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 255,  "Lesser Spirit", "+3 Spirit", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 723,  "Lesser Intellect", "+3 Spirit", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2674, "Spellsurge", "Occasionally restore 100 mana to all nearby party members over 10 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 300 },
                        EnchantDefinition{ 2671, "Sunfire", "+50 Arcane and Fire Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 2672, "Soulfrost", "+54 Frost and Shadow Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 350 },
                        EnchantDefinition{ 2343, "Major Healing", "+81 Healing Power and +27 Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 300 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 2669, "Major Spellpower", "+40 Spell Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 125 },
                        EnchantDefinition{ 2666, "Major Intellect", "+30 Intellect", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 125 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3854, "Greater Spellpower", "+81 Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 600 },
                        EnchantDefinition{ 3834, "Mighty Spellpower", "+63 Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 550 },
                        EnchantDefinition{ 3790, "Black Magic", "Damaging spells sometimes increase haste rating by 250 for 10 seconds", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 550 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3855, "Spellpower", "+69 Spell Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 250 },
                        EnchantDefinition{ 3830, "Exceptional Spellpower", "+50 Spell Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 250 },
                        EnchantDefinition{ 3239, "Icebreaker", "Chance to inflict 180 to 220 Fire damage on strike", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 },
                        EnchantDefinition{ 3844, "Exceptional Spirit", "+45 Spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 165 },
                        EnchantDefinition{ 3241, "Lifeward", "Sometimes heals the wielder for 300 to 400 when striking in melee", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 125 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_Ranged),
                    .name = "Ranged Weapons",
                    .icon = "inv_weapon_bow_11",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2523, "Biznicks 247x128 Accurascope", "+3 Ranged Hit", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 100 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 43,   "Sniper Scope", "+7 Weapon Damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 953,  "Deadly Scope", "+5 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 3 },
                        EnchantDefinition{ 33,   "Accurate Scope", "+3 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 2 },
                        EnchantDefinition{ 32,   "Standard Scope", "+2 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 2 },
                        EnchantDefinition{ 30,   "Crude Scope", "+1 Weapon Damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 1 },
                        // --- VANILLA END ---

                        // --- TBC ---
                       // --- RAID TIER ---
                       EnchantDefinition{ 2724, "Stabilized Eternium Scope", "+28 Ranged Critical Strike Rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 300 },

                       // --- PRE-RAID TIER ---
                       EnchantDefinition{ 2723, "Khorium Scope", "+12 damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 125 },

                       // --- LEVELING TIER ---
                       EnchantDefinition{ 2722, "Adamantite Scope", "+10 damage", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 50 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3608, "Heartseeker Scope", "+40 ranged critical strike rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 550 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3843, "Diamond-cut Refractor Scope", "+15 damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 175 },
                        EnchantDefinition{ 3607, "Sun Scope", "+40 ranged haste rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 250 }
                        // --- WOTLK END ---
                    }
                }
            }
        },
        //Armor Category
        EnchantCategoryDefinition {
            .enchantCategoryId = static_cast<uint32>(EnchantCategory::Armor),
            .name = "Armor enchants",
            .icon = "inv_chest_plate05",
            .subTypes = {
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Helm),
                    .name = "Helm",
                    .icon = "inv_helmet_13",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2588, "Presence of Sight", "+18 Spell Power + & +1% Spell Hit", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_MAGE), 0, 60, 2, 200 },
                        EnchantDefinition{ 2590, "Prophetic Aura", "+10 Stamina, 4 MP5 & 24 Healing Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_PRIEST), 0, 60, 2, 200 },
                        EnchantDefinition{ 2589, "Hoodoo Hex", "+10 Stamina & +18 Spell Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_WARLOCK), 0, 60, 2, 200 },
                        EnchantDefinition{ 2591, "Animist’s Caress", "+10 Stamina, +10 Intellect & +18 Healing Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_DRUID), 0, 60, 2, 200 },
                        EnchantDefinition{ 2585, "Death’s Embrace", "+28 Attack Power & +1% Dodge", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_ROGUE), 0, 60, 2, 200 },
                        EnchantDefinition{ 2586, "Falcon’s Call", "+24 Ranged Attack Power, +10 Stamina & +1% Hit", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_HUNTER), 0, 60, 2, 200 },
                        EnchantDefinition{ 2587, "Vodouisant’s Vigilant Embrace", "+15 Intellect & +13 Spell Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_SHAMAN), 0, 60, 2, 200 },
                        EnchantDefinition{ 2584, "Syncretist’s Sigil", "+10 Stamina, +7 Defense & +24 Healing Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_PALADIN), 0, 60, 2, 200 },
                        EnchantDefinition{ 2583, "Presence of Might", "+10 Stamina, +7 Defense & +15 Shield Block", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_WARRIOR), 0, 60, 2, 200 },
                        EnchantDefinition{ 1508, "Lesser Arcanum of Voracity (Agility)", "+8 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1506, "Lesser Arcanum of Voracity (Strength)", "+8 Strength", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1509, "Lesser Arcanum of Voracity (Intellect)", "+8 Intellect", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1510, "Lesser Arcanum of Voracity (Spirit)", "+8 Spirit", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1507, "Lesser Arcanum of Voracity (Stamina)", "+8 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1390, "Savage Guard", "+10 Nature Resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1503, "Lesser Arcanum of Constitution", "+100 Health", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1505, "Lesser Arcanum of Resilience", "+20 Fire Resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1483, "Lesser Arcanum of Rumination", "+150 Mana", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1504, "Lesser Arcanum of Tenacity", "+125 Armor", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 3646, "Arcanum of Protection", "+1% Dodge", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 2544, "Arcanum of Focus", "+Spell Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 2543, "Arcanum of Rapidity", "+1% Haste", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3002, "Glyph of Power", "+22 Spell Power & +14 Spell Hit Rating", EnchantTier::Raid, "", 0, 935, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 3001, "Glyph of Renewal", "+25 Healing Power, +12 Spell Damage & +7 MP5", EnchantTier::Raid, "", 0, 946, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 3001, "Glyph of Renewal", "+25 Healing Power, +12 Spell Damage & +7 MP5", EnchantTier::Raid, "", 0, 947, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 2999, "Glyph of the Defender", "+16 Defense Rating & +17 Dodge Rating", EnchantTier::Raid, "", 0, 989, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 3003, "Glyph of Ferocity", "+34 Attack Power & +16 Hit Rating", EnchantTier::Raid, "", 0, 942, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 3004, "Glyph of the Gladiator", "+18 Stamina & +20 Resilience Rating", EnchantTier::Raid, "", 0, 1077, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 12, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3006, "Glyph of Arcane Warding", "+20 Arcane Resistance", EnchantTier::PreRaid, "", 0, 935, 5, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 75 },
                        EnchantDefinition{ 3007, "Glyph of Fire Warding", "+20 Fire Resistance", EnchantTier::PreRaid, "", 0, 946, 5, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 75 },
                        EnchantDefinition{ 3007, "Glyph of Fire Warding", "+20 Fire Resistance", EnchantTier::PreRaid, "", 0, 947, 5, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 75 },
                        EnchantDefinition{ 3008, "Glyph of Frost Warding", "+20 Nature Resistance", EnchantTier::PreRaid, "", 0, 942, 5, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 75 },
                        EnchantDefinition{ 3009, "Glyph of Shadow Warding", "+20 Shadow Resistance", EnchantTier::PreRaid, "", 0, 1011, 5, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 75 },
                        EnchantDefinition{ 3096, "Glyph of the Outcast", "+17 Strength & +16 Intellect", EnchantTier::PreRaid, "", 0, 1011, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 100 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 2841, "Heavy Knothide Armor Kit", "+10 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 25 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3820, "Arcanum of Burning Mysteries", "+30 spell power, +20 critical strike rating", EnchantTier::Raid, "", 0, 1090, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3819, "Arcanum of Blissful Mending", "+30 spell power, +10 mp5", EnchantTier::Raid, "", 0, 1091, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3817, "Arcanum of Torment", "+50 attack power, +20 critical strike rating", EnchantTier::Raid, "", 0, 1098, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3818, "Arcanum of the Stalwart Protector", "+37 stamina, +20 defense rating", EnchantTier::Raid, "", 0, 1106, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3842, "Arcanum of the Savage Gladiator", "+30 stamina, +25 resilience rating", EnchantTier::PreRaid, "", 0, 1037, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 300 },
                        EnchantDefinition{ 3842, "Arcanum of the Savage Gladiator", "+30 stamina, +25 resilience rating", EnchantTier::PreRaid, "", 0, 1052, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 300 },
                        EnchantDefinition{ 3797, "Arcanum of Dominance", "+29 spell power, +20 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3797, "Arcanum of Dominance", "+29 spell power, +20 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3795, "Arcanum of Triumph", "+50 attack power, +20 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3795, "Arcanum of Triumph", "+50 attack power, +20 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3815, "Arcanum of the Eclipsed Moon", "+25 arcane resistance, +30 stamina", EnchantTier::PreRaid, "", 0, 1091, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3816, "Arcanum of the Flame's Soul", "+25 fire resistance, +30 stamina", EnchantTier::PreRaid, "", 0, 1090, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3812, "Arcanum of the Frosty Soul", "+25 frost resistance, +30 stamina", EnchantTier::PreRaid, "", 0, 1119, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3813, "Arcanum of Toxic Warding", "+25 nature resistance, +30 stamina", EnchantTier::PreRaid, "", 0, 1098, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3814, "Arcanum of the Fleeing Shadow", "+25 shadow resistance, +30 stamina", EnchantTier::PreRaid, "", 0, 1106, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3878, "Mind Amplification Dish", "+45 stamina, allows user to attempt to control the target (10 min cooldown), requires 410 Engineering", EnchantTier::PreRaid, "Engineering", 410, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 3329, "Borean Armor Kit", "+12 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 40 },
                        EnchantDefinition{ 3330, "Heavy Borean Armor Kit", "+18 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 75 }
                        // --- WOTLK END ---
                    }
                },

                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Shoulders),
                    .name = "Shoulders",
                    .icon = "inv_shoulder_28",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2606, "Zandalar Signet of Might", "+30 Attack Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 2, 200 },
                        EnchantDefinition{ 2604, "Zandalar Signet of Mojo", "+18 Spell Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 2, 200 },
                        EnchantDefinition{ 2605, "Zandalar Signet of Serenity", "+24 Healing Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 2, 200 },
                        EnchantDefinition{ 2717, "Might of the Scourge", "+26 Attack Power, +1% Critical Strike", EnchantTier::Raid, "", 0, 529, 4, static_cast<uint32>(Classes::CLASS_NONE), 1, 60, 6, 300 },
                        EnchantDefinition{ 2721, "Power of the Scourge", "+15 Spell Damage/Healing, +1% Spell Critical Strike", EnchantTier::Raid, "", 0, 529, 4, static_cast<uint32>(Classes::CLASS_NONE), 1, 60, 6, 300 },
                        EnchantDefinition{ 2715, "Fortitude of the Scourge", "+16 Stamina, +100 Armor", EnchantTier::Raid, "", 0, 529, 4, static_cast<uint32>(Classes::CLASS_NONE), 1, 60, 6, 300 },
                        EnchantDefinition{ 2716, "Resilience of the Scourge", "+15 Stamina, +31 Healing Spells", EnchantTier::Raid, "", 0, 529, 4, static_cast<uint32>(Classes::CLASS_NONE), 1, 60, 6, 300 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3242, "Chromatic Mantle of the Dawn", "+5 Resistance", EnchantTier::PreRaid, "", 0, 529, 3, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 2, 50 },

                        EnchantDefinition{ 3242, "Chromatic Mantle of the Dawn", "+5 Resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 2, 50 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2986, "Greater Inscription of Vengeance", "+30 Attack Power and +10 Critical Strike Rating", EnchantTier::Raid, "", 0, 932, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 2978, "Greater Inscription of Warding", "+15 Dodge Rating and +10 Defense Rating", EnchantTier::Raid, "", 0, 932, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 2982, "Greater Inscription of Discipline", "+18 Spell Power and +10 Spell Critical Strike Rating", EnchantTier::Raid, "", 0, 932, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 2980, "Greater Inscription of Faith", "+33 Healing Power, +11 Spell Power and +4 MP5", EnchantTier::Raid, "", 0, 932, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 2997, "Greater Inscription of the Blade", "+15 Critical Strike Rating and +20 Attack Power", EnchantTier::Raid, "", 0, 934, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 2995, "Greater Inscription of the Orb", "+15 Spell Critical Strike Rating and +12 Power", EnchantTier::Raid, "", 0, 934, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 2991, "Greater Inscription of the Knight", "+15 Defense Rating and +10 Dodge Rating", EnchantTier::Raid, "", 0, 934, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },
                        EnchantDefinition{ 2993, "Greater Inscription of the Oracle", "+6 MP5 and +22 Healing Power", EnchantTier::Raid, "", 0, 934, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 8, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 2983, "Inscription of Vengeance", "+26 Attack Power", EnchantTier::PreRaid, "", 0, 932, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 64, 8, 75 },
                        EnchantDefinition{ 2977, "Inscription of Warding", "+13 Dodge Rating", EnchantTier::PreRaid, "", 0, 932, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 64, 8, 75 },
                        EnchantDefinition{ 2981, "Inscription of Discipline", "+15 Spell Power", EnchantTier::PreRaid, "", 0, 932, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 64, 8, 75 },
                        EnchantDefinition{ 2979, "Inscription of Faith", "+29 Healing Power and +10 Spell Power", EnchantTier::PreRaid, "", 0, 932, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 64, 8, 75 },
                        EnchantDefinition{ 2996, "Inscription of the Blade", "+13 Critical Strike Rating", EnchantTier::PreRaid, "", 0, 934, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 64, 8, 75 },
                        EnchantDefinition{ 2994, "Inscription of the Orb", "+13 Spell Critical Strike Rating", EnchantTier::PreRaid, "", 0, 934, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 64, 8, 75 },
                        EnchantDefinition{ 2990, "Inscription of the Knight", "+13 Defense Rating", EnchantTier::PreRaid, "", 0, 934, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 64, 8, 75 },
                        EnchantDefinition{ 2992, "Inscription of the Oracle", "+5 MP5", EnchantTier::PreRaid, "", 0, 934, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 64, 8, 75 },
                        EnchantDefinition{ 2998, "Inscription of Endurance", "+7 All Resistances", EnchantTier::PreRaid, "", 0, 967, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 70, 1, 75 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 2841, "Heavy Knothide Armor Kit", "+10 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 25 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3808, "Greater Inscription of the Axe", "+40 attack power, +15 critical strike rating", EnchantTier::Raid, "", 0, 1119, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3809, "Greater Inscription of the Crag", "+24 spell power, +6 mp5", EnchantTier::Raid, "", 0, 1119, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3811, "Greater Inscription of the Pinnacle", "+20 dodge rating, +15 defense rating", EnchantTier::Raid, "", 0, 1119, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3810, "Greater Inscription of the Storm", "+24 spell power, +15 critical strike rating", EnchantTier::Raid, "", 0, 1119, 7, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3875, "Lesser Inscription of the Axe", "+30 attack power, +10 critical strike rating", EnchantTier::PreRaid, "", 0, 1119, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3807, "Lesser Inscription of the Crag", "+18 spell power, +4 mp5", EnchantTier::PreRaid, "", 0, 1119, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3876, "Lesser Inscription of the Pinnacle", "+15 dodge rating, +10 defense rating", EnchantTier::PreRaid, "", 0, 1119, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3806, "Lesser Inscription of the Storm", "+18 spell power, +10 critical strike rating", EnchantTier::PreRaid, "", 0, 1119, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3835, "Master’s Inscription of the Axe", "+120 attack power, +15 critical strike rating, requires 400 Inscription", EnchantTier::PreRaid, "Inscription", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3836, "Master’s Inscription of the Crag", "+70 spell power, +8 mp5, requires 400 Inscription", EnchantTier::PreRaid, "Inscription", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3837, "Master’s Inscription of the Pinnacle", "+60 dodge rating, +15 defense rating, requires 400 Inscription", EnchantTier::PreRaid, "Inscription", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3838, "Master’s Inscription of the Storm", "+70 spell power, +15 critical strike rating, requires 400 Inscription", EnchantTier::PreRaid, "Inscription", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3852, "Greater Inscription of the Gladiator", "+30 stamina, +15 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3793, "Inscription of Triumph", "+40 attack power, +15 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3793, "Inscription of Triumph", "+40 attack power, +15 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3794, "Inscription of Dominance", "+23 spell power, +15 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3794, "Inscription of Dominance", "+23 spell power, +15 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 3329, "Borean Armor Kit", "+12 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 40 },
                        EnchantDefinition{ 3330, "Heavy Borean Armor Kit", "+18 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 75 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Cloak),
                    .name = "Cloak",
                    .icon = "inv_misc_cape_20",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 910,  "Stealth", "Increase to stealth", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 5, 200 },
                        EnchantDefinition{ 2622, "Dodge", "+1% Dodge", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 5, 200 },
                        EnchantDefinition{ 2619, "Greater Fire Resistance", "+15 Fire Resistance", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 2620, "Greater Nature Resistance", "+15 Nature Resistance", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 804,  "Lesser Shadow Resistance", "+10 Shadow Resistance", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1888, "Greater Resistance", "+5 Resistance", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 2621, "Subtlety", "-2% Threat", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 100 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 2463, "Fire Resistance", "+7 Fire Resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1899, "Superior Defense", "+70 Armor", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 884,  "Greater Defense", "+50 Armor", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 849,  "Lesser Agility", "+3 Agility", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 247,  "Minor Agility", "+1 Agility", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 256,  "Lesser Fire Resistance", "+5 Fire Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 9 },
                        EnchantDefinition{ 903,  "Resistance", "+3 Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 65,   "Minor Resistance", "+1 Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 848,  "Defense", "+30 Armor", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 7 },
                        EnchantDefinition{ 744,  "Lesser Protection", "+20 Armor", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 7 },
                        EnchantDefinition{ 783,  "Minor Protection", "+10 Armor", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2938, "Spell Penetration", "+20 Spell Penetration", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 150 },
                        EnchantDefinition{ 368,  "Greater Agility", "+12 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },
                        EnchantDefinition{ 2664, "Major Resistance", "+7 Resistance", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 1257, "Greater Arcane Resistance", "+15 Arcane Resistance", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 1441, "Greater Shadow Resistance", "+15 Shadow Resistance", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 2648, "Steelweave", "+12 Defense Rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 2662, "Major Armor", "+120 Armor", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3831, "Greater Speed", "+23 haste rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 1099, "Major Agility", "+22 agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3294, "Mighty Armor", "+225 armor", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3256, "Shadow Armor", "+10 agility, slight increase to stealth", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3825, "Speed", "+15 haste rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3243, "Spell Piercing", "+35 spell penetration", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 983,  "Superior Agility", "+16 agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1262, "Superior Arcane Resistance", "+20 arcane resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1354, "Superior Fire Resistance", "+20 fire resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3230, "Superior Frost Resistance", "+20 frost resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1400, "Superior Nature Resistance", "+20 nature resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1446, "Superior Shadow Resistance", "+20 shadow resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1951, "Titanweave", "+16 defense rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3296, "Wisdom", "+10 spirit, slight decrease in threat", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3728, "Darkglow Embroidery", "Chance to restore 400 mana when you cast a spell, requires 400 Tailoring", EnchantTier::PreRaid, "Tailoring", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3722, "Lightweave Embroidery", "Chance to increase your spell power by 295 for 15 sec when casting a spell, requires 400 Tailoring", EnchantTier::PreRaid, "Tailoring", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3730, "Swordguard Embroidery", "Chance for your damaging melee and ranged attacks to sometimes increase your attack power by 400 for 15 sec, requires 400 Tailoring", EnchantTier::PreRaid, "Tailoring", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3605, "Flexweave Underlay", "Turn your cloak into a parachute in order to fall slowly for 30 sec (1 min cooldown), also increases agility by 23, requires 400 Engineering", EnchantTier::PreRaid, "Engineering", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 0,    "Springy Arachnoweave", "+27 Spell Power and Parachute (Slow Fall 30 sec)", EnchantTier::PreRaid, "Engineering", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 75, 1, 100 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Chest),
                    .name = "Chest",
                    .icon = "inv_chest_plate05",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 1891, "Greater Stats", "+4 All Stats", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 928,  "Stats", "+3 All Stats", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1892, "Major Health", "+100 Health", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 1893, "Major Mana", "+100 Mana", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 866,  "Lesser Stats", "+2 All Stats", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 847,  "Minor Stats", "+1 All Stats", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 908,  "Superior Health", "+50 Health", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 850,  "Greater Health", "+35 Health", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 254,  "Health", "+25 Health", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 242,  "Lesser Health", "+15 Health", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 41,   "Minor Health", "+5 Health", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 913,  "Superior Mana", "+65 Mana", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 857,  "Greater Mana", "+50 Mana", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 843,  "Mana", "+30 Mana", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 246,  "Lesser Mana", "+20 Mana", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 24,   "Minor Mana", "+5 Mana", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 63,   "Lesser Absorption", "", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 44,   "Minor Absorption", "", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2661, "Exceptional Stats", "+6 All Stats", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 250 },
                        EnchantDefinition{ 3150, "Restore Mana Prime", "+6 MP5", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },
                        EnchantDefinition{ 2933, "Major Resilience", "+15 Resilience Rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1950, "Defense", "+15 Defense Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 2659, "Exceptional Health", "+150 Health", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 1144, "Major Spirit", "+15 Spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 2841, "Heavy Knothide Armor Kit", "+10 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 25 },
                        EnchantDefinition{ 2792, "Knothide Armor Kit", "+8 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2793, "Vindicator’s Armor Kit", "+8 Defense Rating", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 20 },
                        EnchantDefinition{ 2794, "Magister’s Armor Kit", "+3 MP5", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 20 },
                        EnchantDefinition{ 2989, "Arcane Armor Kit", "+8 Arcane Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2985, "Flame Armor Kit", "+8 Fire Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2987, "Frost Armor Kit", "+8 Frost Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2988, "Nature Armor Kit", "+8 Nature Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2984, "Shadow Armor Kit", "+8 Shadow Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3832, "Powerful Stats", "+10 all stats", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 450 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3233, "Exceptional Mana", "+250 mana", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 200 },
                        EnchantDefinition{ 3245, "Exceptional Resilience", "+20 resilience rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1953, "Greater Defense", "+22 defense rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 2381, "Greater Mana Restoration", "+10 mp5", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3236, "Mighty Health", "+200 health", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 200 },
                        EnchantDefinition{ 3297, "Super Health", "+275 health", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3252, "Super Stats", "+8 all stats", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 3329, "Borean Armor Kit", "+12 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 40 },
                        EnchantDefinition{ 3330, "Heavy Borean Armor Kit", "+18 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 75 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Bracers),
                    .name = "Bracers",
                    .icon = "inv_bracer_14",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2566, "Healing Power", "+24 Healing Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 2565, "Mana Regeneration", "+4 MP5", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 1883, "Greater Intellect", "+7 Intellect", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 1885, "Superior Strength", "+9 Strength", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 1884, "Superior Spirit", "+9 Spirit", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 1886, "Superior Stamina", "+9 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 929,  "Greater Stamina", "+7 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 927,  "Greater Strength", "+7 Strength", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 907,  "Greater Spirit", "+7 Spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 905,  "Intellect", "+5 Intellect", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 856,  "Strength", "+5 Strength", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 247,  "Minor Agility", "+1 Agility", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 923,  "Deflection", "+3 Defense", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 925,  "Lesser Deflection", "+2 Defense", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 924,  "Minor Deflect", "+1 Defense", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 41,   "Minor Health", "+5 Health", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 66,   "Minor Stamina", "+1 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 724,  "Lesser Stamina", "+3 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 852,  "Stamina", "+5 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 243,  "Minor Spirit", "+1 Spirit", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 255,  "Lesser Spirit", "+3 Spirit", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 851,  "Spirit", "+5 Spirit", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 248,  "Minor Strength", "+1 Strength", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 823,  "Lesser Strength", "+3 Strength", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 723,  "Lesser Intellect", "+3 Intellect", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2650, "Spellpower", "+15 Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 250 },
                        EnchantDefinition{ 2617, "Superior Healing", "+30 Healing Power and +10 Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 250 },
                        EnchantDefinition{ 2679, "Restore Mana Prime", "+6 MP5", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },
                        EnchantDefinition{ 1593, "Assault", "+24 Attack Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },
                        EnchantDefinition{ 2648, "Major Defense", "+12 Defense Rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },
                        EnchantDefinition{ 2649, "Fortitude", "+12 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 250 },
                        EnchantDefinition{ 2647, "Brawn", "+12 Strength", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1891, "Stats", "+4 All Stats", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 369,  "Major Intellect", "+12 Intellect", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3845, "Greater Assault", "+50 attack power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3850, "Major Stamina", "+40 stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 2332, "Superior Spellpower", "+30 spell power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1119, "Exceptional Intellect", "+16 intellect", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3231, "Expertise", "+15 expertise rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 2326, "Greater Spellpower", "+23 spell power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 2661, "Greater Stats", "+6 all stats", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 1147, "Major Spirit", "+18 spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1600, "Striking", "+38 attack power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3756, "Fur Lining — Attack Power", "+130 attack power, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3758, "Fur Lining — Spell Power", "+76 spell power, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3757, "Fur Lining — Stamina", "+102 stamina, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3763, "Fur Lining — Arcane Resist", "+70 arcane resistance, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3759, "Fur Lining — Fire Resist", "+70 fire resistance, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3760, "Fur Lining — Frost Resist", "+70 frost resistance, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3762, "Fur Lining — Nature Resist", "+70 nature resistance, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3761, "Fur Lining — Shadow Resist", "+70 shadow resistance, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3717, "Socket Bracer", "Adds a gem socket to bracers; requires 400 Blacksmithing and stacks with other enchants", EnchantTier::PreRaid, "Blacksmithing", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Gloves),
                    .name = "Gloves",
                    .icon = "inv_gauntlets_24",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2617, "Healing Power", "+30 Healing Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 5, 200 },
                        EnchantDefinition{ 2614, "Shadow Power", "+20 Shadow Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 5, 200 },
                        EnchantDefinition{ 2615, "Frost Power", "+20 Frost Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 5, 200 },
                        EnchantDefinition{ 2616, "Fire Power", "+20 Fire Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 5, 200 },
                        EnchantDefinition{ 2564, "Superior Agility", "+15 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 5, 200 },
                        EnchantDefinition{ 1887, "Greater Agility", "+7 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 2613, "Threat", "+2% Threat", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 5, 200 },
                        EnchantDefinition{ 927,  "Greater Strength", "+7 Strength", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 931,  "Minor Haste", "+1% Melee Haste", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 930,  "Riding Skill", "", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 865,  "Skinning", "+5 Skinning", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 906,  "Advanced Mining", "+5 Mining", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 909,  "Advanced Herbalism", "+5 Herbalism", EnchantTier::PreRaid, "Herbalism", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 904,  "Agility", "+5 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 856,  "Strength", "+5 Strength", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 845,  "Herbalism", "+2 Herbalism", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 25 },
                        EnchantDefinition{ 846,  "Fishing", "+2 Fishing", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 25 },
                        EnchantDefinition{ 844,  "Mining", "+2 Mining", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 25 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2937, "Major Spellpower", "+20 Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 250 },
                        EnchantDefinition{ 2322, "Major Healing", "+35 Healing Power and +12 Spell Power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 250 },
                        EnchantDefinition{ 2935, "Spell Strike", "+15 Spell Hit Rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },
                        EnchantDefinition{ 1594, "Assault", "+26 attack power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 2934, "Blasting", "+10 Spell Critical Strike Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 3260, "Glove Reinforcements", "+240 armor", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 2841, "Heavy Knothide Armor Kit", "+10 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 25 },
                        EnchantDefinition{ 2792, "Knothide Armor Kit", "+8 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2793, "Vindicator’s Armor Kit", "+8 Defense Rating", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 20 },
                        EnchantDefinition{ 2794, "Magister’s Armor Kit", "+3 MP5", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 20 },
                        EnchantDefinition{ 2989, "Arcane Armor Kit", "+8 Arcane Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2985, "Flame Armor Kit", "+8 Fire Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2987, "Frost Armor Kit", "+8 Frost Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2988, "Nature Armor Kit", "+8 Nature Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2984, "Shadow Armor Kit", "+8 Shadow Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 1603, "Crusher", "+44 attack power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3253, "Armsman", "+10 parry rating, 2% increase to threat", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3246, "Exceptional Spellpower", "+28 spell power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3231, "Expertise", "+15 expertise rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3238, "Gatherer", "+5 herbalism, +5 mining, +5 skinning", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 150 },
                        EnchantDefinition{ 3829, "Greater Assault", "+35 attack power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3222, "Major Agility", "+20 agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3234, "Precision", "+20 hit rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3603, "Hand-Mounted Pyro Rocket", "Deal 1645 to 2020 fire damage to an enemy at range (45 sec cooldown), requires 400 Engineering", EnchantTier::PreRaid, "Engineering", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3604, "Hyperspeed Accelerators", "Increases your haste rating by 340 for 12 sec (1 minute cooldown), requires 400 Engineering", EnchantTier::PreRaid, "Engineering", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3860, "Reticulated Armor Webbing", "Increases armor by 885, requires 400 Engineering", EnchantTier::PreRaid, "Engineering", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3723, "Socket Gloves", "Adds a gem socket to gloves; requires 400 Blacksmithing and stacks with other enchants", EnchantTier::PreRaid, "Blacksmithing", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 3329, "Borean Armor Kit", "+12 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 40 },
                        EnchantDefinition{ 3330, "Heavy Borean Armor Kit", "+18 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 75 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Waist),
                    .name = "Belt",
                    .icon = "inv_belt_23",
                    .enchants = {
                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3729, "Eternal Belt Buckle", "Adds a gem socket to belts", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 150 },
                        EnchantDefinition{ 3599, "Personal Electromagnetic Pulse Generator", "Can confuse nearby mechanical creatures (1 minute cooldown), requires 400 Engineering", EnchantTier::Raid, "Engineering", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3601, "Frag Belt", "Attach a miniaturized explosive assembly to your belt, allowing you to detach and throw a Cobalt Frag Bomb every 6 minutes, requires 400 Engineering", EnchantTier::Raid, "Engineering", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Legs),
                    .name = "Legs",
                    .icon = "inv_pants_06",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2588, "Presence of Sight", "+18 Spell Power + & +1% Spell Hit", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_MAGE), 0, 60, 2, 200 },
                        EnchantDefinition{ 2590, "Prophetic Aura", "+10 Stamina, 4 MP5 & 24 Healing Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_PRIEST), 0, 60, 2, 200 },
                        EnchantDefinition{ 2589, "Hoodoo Hex", "+10 Stamina & +18 Spell Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_WARLOCK), 0, 60, 2, 200 },
                        EnchantDefinition{ 2591, "Animist’s Caress", "+10 Stamina, +10 Intellect & +18 Healing Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_DRUID), 0, 60, 2, 200 },
                        EnchantDefinition{ 2585, "Death’s Embrace", "+28 Attack Power & +1% Dodge", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_ROGUE), 0, 60, 2, 200 },
                        EnchantDefinition{ 2586, "Falcon’s Call", "+24 Ranged Attack Power, +10 Stamina & +1% Hit", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_HUNTER), 0, 60, 2, 200 },
                        EnchantDefinition{ 2587, "Vodouisant’s Vigilant Embrace", "+15 Intellect & +13 Spell Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_SHAMAN), 0, 60, 2, 200 },
                        EnchantDefinition{ 2584, "Syncretist’s Sigil", "+10 Stamina, +7 Defense & +24 Healing Power", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_PALADIN), 0, 60, 2, 200 },
                        EnchantDefinition{ 2583, "Presence of Might", "+10 Stamina, +7 Defense & +15 Shield Block", EnchantTier::Raid, "", 0, 270, 4, static_cast<uint32>(Classes::CLASS_WARRIOR), 0, 60, 2, 200 },
                        EnchantDefinition{ 1508, "Lesser Arcanum of Voracity (Agility)", "+8 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1506, "Lesser Arcanum of Voracity (Strength)", "+8 Strength", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1509, "Lesser Arcanum of Voracity (Intellect)", "+8 Intellect", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1510, "Lesser Arcanum of Voracity (Spirit)", "+8 Spirit", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1507, "Lesser Arcanum of Voracity (Stamina)", "+8 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1390, "Savage Guard", "+10 Nature Resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1503, "Lesser Arcanum of Constitution", "+100 Health", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1505, "Lesser Arcanum of Resilience", "+20 Fire Resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1483, "Lesser Arcanum of Rumination", "+150 Mana", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 1504, "Lesser Arcanum of Tenacity", "+125 Armor", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 3646, "Arcanum of Protection", "+1% Dodge", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 2544, "Arcanum of Focus", "+Spell Power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        EnchantDefinition{ 2543, "Arcanum of Rapidity", "+1% Haste", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 2, 50 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3013, "Nethercleft Leg Armor", "+12 Agility and +40 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 300 },
                        EnchantDefinition{ 3012, "Nethercobra Leg Armor", "+50 Attack Power and +12 Critical Strike Rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 300 },
                        EnchantDefinition{ 2748, "Runic Spellthread", "+35 Spell Power & +20 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 300 },
                        EnchantDefinition{ 2746, "Golden Spellthread", "+66 Healing Power, +22 Spell Power & +20 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 300 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3011, "Clefthide Leg Armor", "+10 Agility and +30 Stamina", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 3010, "Cobrahide Leg Armor", "+40 Attack Power and +10 Critical Strike Rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 2747, "Mystic Spellthread", "+25 Spell Power & +15 Stamina", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 2745, "Silver Spellthread", "+46 Healing Power, +16 Spell Power & +15 Stamina", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 2841, "Heavy Knothide Armor Kit", "+10 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 25 },
                        EnchantDefinition{ 2792, "Knothide Armor Kit", "+8 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2793, "Vindicator’s Armor Kit", "+8 Defense Rating", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 20 },
                        EnchantDefinition{ 2794, "Magister’s Armor Kit", "+3 MP5", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 20 },
                        EnchantDefinition{ 2989, "Arcane Armor Kit", "+8 Arcane Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2985, "Flame Armor Kit", "+8 Fire Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2987, "Frost Armor Kit", "+8 Frost Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2988, "Nature Armor Kit", "+8 Nature Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2984, "Shadow Armor Kit", "+8 Shadow Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3822, "Frosthide Leg Armor", "+22 agility, +55 stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3823, "Icescale Leg Armor", "+75 attack power, +22 critical strike rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3719, "Brilliant Spellthread", "+50 spell power, +20 spirit", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3721, "Sapphire Spellthread", "+50 spell power, +30 stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3853, "Earthen Leg Armor", "+40 resilience rating, +28 stamina", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3325, "Jormungar Leg Armor", "+15 agility, +45 stamina", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3326, "Nerubian Leg Armor", "+55 attack power, +15 critical strike rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3720, "Azure Spellthread", "+35 spell power, +20 stamina", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3718, "Shining Spellthread", "+35 spell power, +12 spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3327, "Jormungar Leg Reinforcements", "+22 agility, +55 stamina, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3328, "Nerubian Leg Reinforcements", "+75 attack power, +22 critical strike rating, requires 400 Leatherworking", EnchantTier::PreRaid, "Leatherworking", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3873, "Master’s Spellthread", "+50 spell power, +30 stamina, requires 400 Tailoring", EnchantTier::PreRaid, "Tailoring", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3872, "Sanctified Spellthread", "+50 spell power, +20 spirit, requires 400 Tailoring", EnchantTier::PreRaid, "Tailoring", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 3329, "Borean Armor Kit", "+12 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 40 },
                        EnchantDefinition{ 3330, "Heavy Borean Armor Kit", "+18 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 75 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Ring_Slot1),
                    .name = "Ring",
                    .icon = "inv_jewelry_ring_22",
                    .enchants = {
                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2930, "Healing Power", "+20 Healing Power and +7 Spell Power, requires 370 Enchanting", EnchantTier::Raid, "Enchanting", 370, 935, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 35, 8, 30 },
                        EnchantDefinition{ 2928, "Spellpower", "+12 Spell Power, requires 360 Enchanting", EnchantTier::Raid, "Enchanting", 360, 989, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 35, 8, 30 },
                        EnchantDefinition{ 2931, "Stats", "+4 All Stats, requires 375 Enchanting", EnchantTier::Raid, "Enchanting", 375, 1011, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 35, 8, 30 },
                        EnchantDefinition{ 2929, "Striking", "+2 Damage, requires 360 Enchanting", EnchantTier::Raid, "Enchanting", 360, 933, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 35, 8, 30 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3839, "Enchant Ring — Assault", "+40 attack power, requires 400 Enchanting", EnchantTier::Raid, "Enchanting", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3840, "Enchant Ring — Greater Spellpower", "+23 spell power, requires 400 Enchanting", EnchantTier::Raid, "Enchanting", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3791, "Enchant Ring — Stamina", "+30 stamina, requires 400 Enchanting", EnchantTier::PreRaid, "Enchanting", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Ring_Slot2),
                    .name = "Ring",
                    .icon = "inv_jewelry_ring_22",
                    .enchants = {
                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2930, "Healing Power", "+20 Healing Power and +7 Spell Power, requires 370 Enchanting", EnchantTier::Raid, "Enchanting", 370, 935, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 35, 8, 30 },
                        EnchantDefinition{ 2928, "Spellpower", "+12 Spell Power, requires 360 Enchanting", EnchantTier::Raid, "Enchanting", 360, 989, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 35, 8, 30 },
                        EnchantDefinition{ 2931, "Stats", "+4 All Stats, requires 375 Enchanting", EnchantTier::Raid, "Enchanting", 375, 1011, 4, static_cast<uint32>(Classes::CLASS_NONE), 0, 35, 8, 30 },
                        EnchantDefinition{ 2929, "Striking", "+2 Damage, requires 360 Enchanting", EnchantTier::Raid, "Enchanting", 360, 933, 6, static_cast<uint32>(Classes::CLASS_NONE), 0, 35, 8, 30 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 3839, "Enchant Ring — Assault", "+40 attack power, requires 400 Enchanting", EnchantTier::Raid, "Enchanting", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3840, "Enchant Ring — Greater Spellpower", "+23 spell power, requires 400 Enchanting", EnchantTier::Raid, "Enchanting", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },
                        EnchantDefinition{ 3791, "Enchant Ring — Stamina", "+30 stamina, requires 400 Enchanting", EnchantTier::PreRaid, "Enchanting", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Boots),
                    .name = "Boots",
                    .icon = "inv_boots_plate_09",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 1887, "Greater Agility", "+7 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 929,  "Greater Stamina", "+7 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 911,  "Minor Speed", "", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 851,  "Spirit", "+5 Spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 852,  "Stamina", "+5 Stamina", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },
                        EnchantDefinition{ 904,  "Agility", "+5 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 724,  "Lesser Stamina", "+3 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 66,   "Minor Stamina", "+1 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 849,  "Lesser Agility", "+3 Agility", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 247,  "Minor Agility", "+1 Agility", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2940, "Boar’s Speed", "+8% Speed & +9 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 250 },
                        EnchantDefinition{ 2939, "Cat’s Swiftness", "+8% Speed & +6 Agility", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 250 },
                        EnchantDefinition{ 2658, "Surefooted", "+10 Hit Rating & +5% Snare and Root Resistance", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 2657, "Dexterity", "+12 Agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 2649, "Fortitude", "+12 Stamina", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 2656, "Vitality", "+4 HP5 and MP5", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 2841, "Heavy Knothide Armor Kit", "+10 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 25 },
                        EnchantDefinition{ 2792, "Knothide Armor Kit", "+8 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2793, "Vindicator’s Armor Kit", "+8 Defense Rating", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 20 },
                        EnchantDefinition{ 2794, "Magister’s Armor Kit", "+3 MP5", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 20 },
                        EnchantDefinition{ 2989, "Arcane Armor Kit", "+8 Arcane Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2985, "Flame Armor Kit", "+8 Fire Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2987, "Frost Armor Kit", "+8 Frost Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2988, "Nature Armor Kit", "+8 Nature Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        EnchantDefinition{ 2984, "Shadow Armor Kit", "+8 Shadow Resistance", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 15 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 1597, "Enchant Boots — Greater Assault", "+32 attack power", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3826, "Enchant Boots — Icewalker", "+12 critical strike rating, +12 hit rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },
                        EnchantDefinition{ 3232, "Enchant Boots — Tuskarr’s Vitality", "+15 stamina, +8% run speed", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 400 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3824, "Enchant Boots — Assault", "+24 attack power", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1075, "Enchant Boots — Greater Fortitude", "+22 stamina", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1147, "Enchant Boots — Greater Spirit", "+18 spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 3244, "Enchant Boots — Greater Vitality", "+7 hp5, +7 mp5", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 983,  "Enchant Boots — Superior Agility", "+16 agility", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3606, "Nitro Boosts", "Increases your critical strike rating by 24 and allows you to greatly increase run speed for 5 sec. 3 minute cooldown, requires 400 Engineering", EnchantTier::PreRaid, "Engineering", 400, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 30 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 3329, "Borean Armor Kit", "+12 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 40 },
                        EnchantDefinition{ 3330, "Heavy Borean Armor Kit", "+18 stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 75 }
                        // --- WOTLK END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Subtype_Shield),
                    .name = "Shield",
                    .icon = "inv_shield_10",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 1890, "Superior Spirit", "+9 Spirit", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 929,  "Greater Stamina", "+7 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },
                        EnchantDefinition{ 926,  "Frost Resistance", "+8 Frost Res", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 907,  "Greater Spirit", "+7 Spirit", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 852,  "Stamina", "+5 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 724,  "Lesser Stamina", "+3 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 66,   "Minor Stamina", "+1 Stamina", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 851,  "Spirit", "+5 Spirit", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 255,  "Lesser Spirit", "+3 Spirit", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 848,  "Lesser Protection", "+30 Armor", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        EnchantDefinition{ 863,  "Lesser Block", "+2% Block", EnchantTier::Leveling, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 1, 1, 1, 5 },
                        // --- VANILLA END ---

                        // --- TBC ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2655, "Shield Block", "+15 Block Rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 150 },
                        EnchantDefinition{ 2653, "Tough Shield", "+18 Block Value", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 150 },
                        EnchantDefinition{ 3229, "Resilience", "+12 Resilience Rating", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 150 },
                        EnchantDefinition{ 1071, "Major Stamina", "+18 Stamina", EnchantTier::Raid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1888, "Resistance", "+5 Resistance", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 75 },
                        EnchantDefinition{ 2654, "Intellect", "+12 Intellect", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 8, 100 },
                        EnchantDefinition{ 2714, "Felsteel Shield Spike", "+26-38 Damage when blocking", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 8, 100 },
                        // --- TBC END ---

                        // --- WOTLK ---
                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1952, "Enchant Shield — Defense", "+20 defense rating", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 225 },
                        EnchantDefinition{ 1128, "Enchant Shield — Greater Intellect", "+25 intellect", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 275 },
                        EnchantDefinition{ 3849, "Titanium Plating", "+81 block value and reduces the duration of disarm effects by 50%", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 300 },
                        EnchantDefinition{ 3748, "Titanium Shield Spike", "+45-67 block damage", EnchantTier::PreRaid, "", 0, 0, 0, static_cast<uint32>(Classes::CLASS_NONE), 0, 60, 13, 150 }
                        // --- WOTLK END ---
                    }
                }
            }
        }
    };
}

//Return all enchants.
const std::vector<EnchantCategoryDefinition>& NPCEnchanterEnhancedEnchantManager::GetEnchantDatabase() const
{
    return m_enchantDatabase;
}

//Find EnchantDefinition by enchant ID.
const EnchantDefinition* NPCEnchanterEnhancedEnchantManager::GetEnchantDefinition(uint32 enchantId) const
{
    for (const auto& cat : m_enchantDatabase)
    {
        for (const auto& subCat : cat.subTypes)
        {
            for (const auto& enchant : subCat.enchants)
            {
                if (enchant.enchantId == enchantId)
                    return &enchant;
            }
        }
    }
    return nullptr;
}

//Check if the subcategorys enchant-list is empty.
bool NPCEnchanterEnhancedEnchantManager::SubCategoryHasNoEnchants(uint32 subCategoryId) const
{
    for (const auto& cat : m_enchantDatabase)
    {
        for (const auto& subCat : cat.subTypes)
        {
            if (subCat.enchantCategorySubTypeId == subCategoryId)
            {
                return subCat.enchants.empty();
            }
        }
    }
    return true;
}

//Check if all enchants are locked behind profession, to lock the whole category.
bool NPCEnchanterEnhancedEnchantManager::AllEnchantsInSubCategoryHasProfessionRequirements(uint32 subCategoryId) const
{
    for (const auto& cat : m_enchantDatabase)
    {
        for (const auto& subCat : cat.subTypes)
        {
            if (subCat.enchantCategorySubTypeId == subCategoryId)
            {
                if (subCat.enchants.empty())
                    return false;

                for (const auto& enchant : subCat.enchants)
                {
                    if (enchant.professionRequirement.empty())
                        return false;
                }
                return true;
            }
        }
    }
    return false;
}

//Check if all enchants are locked behind profession, to lock the whole category.
std::string NPCEnchanterEnhancedEnchantManager::GetProfessionLockedPhrase(uint32 subCategoryId) const
{
    for (const auto& cat : m_enchantDatabase)
    {
        for (const auto& subCat : cat.subTypes)
        {
            if (subCat.enchantCategorySubTypeId == subCategoryId)
            {
                if (subCat.enchants.empty())
                    return "";

                std::string profession = "";
                uint32 professionLowestSkill = 0;

                for (const auto& enchant : subCat.enchants)
                {
                    if (!enchant.professionRequirement.empty())
                    {
                        profession = enchant.professionRequirement;

                        professionLowestSkill = std::max(
                            enchant.professionSkillRequirement,
                            professionLowestSkill);
                    }
                }

                if (!profession.empty() && professionLowestSkill > 0)
                {
                    return " (Requires " + std::to_string(professionLowestSkill) + " " + profession + ")";
                }

                return "";
            }
        }
    }

    return "";
}

//Cache for pricing (Due to the variance, we need to cache the calculated price so it does not differ from menu and subtraction.
//This function both sets and gets the price value for that playerGUID and enchantID.
uint32 NPCEnchanterEnhancedEnchantManager::GetOrCacheEnchantPrice(Player* player, const EnchantDefinition* enchantDef, uint32 subCatId)
{
    if (!player || !enchantDef)
        return 0;

    uint32 playerGuid = player->GetGUID().GetCounter();
    uint32 enchantId = enchantDef->enchantId;
    auto now = std::chrono::steady_clock::now();

    //Get itemGUID to
    EquipmentSlots targetSlot = GetEquipmentSlotFromSubCategory(subCatId);
    Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, targetSlot);
    uint64 currentItemGuid = targetItem ? targetItem->GetGUID().GetCounter() : 0;

    auto playerCacheIt = m_playerPriceCache.find(playerGuid);
    if (playerCacheIt != m_playerPriceCache.end())
    {
        // Check if cache for the player is older than NPCEnchanterEnhancedDynamicPriceCacheDuration. If it is, calculate a new price.
        for (auto it = playerCacheIt->second.begin(); it != playerCacheIt->second.end(); )
        {
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.timestamp).count();
            if (elapsed >= NPCEnchanterEnhancedDynamicPriceCacheDurationInSeconds)
            {
                it = playerCacheIt->second.erase(it);
            }
            else
            {
                ++it;
            }
        }

        auto enchantIt = playerCacheIt->second.find(enchantId);
        if (enchantIt != playerCacheIt->second.end())
        {
            if (enchantIt->second.itemGuid == currentItemGuid)
            {
                return enchantIt->second.price;
            }
            else
            {
                playerCacheIt->second.erase(enchantIt);
            }
        }
    }

    // Calculate fresh price if not found or expired
    uint32 finalPrice = PriceHelper::GetEnchantPriceInGold(player, enchantDef, subCatId);
    m_playerPriceCache[playerGuid][enchantId] = { finalPrice, currentItemGuid, now };

    return finalPrice;
}

//Clear a specific players cache.
void NPCEnchanterEnhancedEnchantManager::ClearPlayerPriceCache(uint32 playerGuid)
{
    LOG_INFO("server.loading", "NPCEnchanterEnhanced - ClearPlayerPriceCache PlayerGUID {},", playerGuid);
    m_playerPriceCache.erase(playerGuid);
}

//Clear all players cache.
void NPCEnchanterEnhancedEnchantManager::ClearAllPlayerPriceCaches()
{
    m_playerPriceCache.clear();
}
