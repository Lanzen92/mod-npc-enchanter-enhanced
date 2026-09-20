/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

#include "EnchantManager.h"
#include <algorithm>
#include <string>

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
                        EnchantDefinition{ 2564, "Agility", "+15 Agility", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 2563, "Strength", "+15 Strength", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 1900, "Crusader", "", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1894, "Icy Weapon", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 803,  "Fiery Weapon", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1897, "Superior Striking", "+5 Weapon Damage", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 25 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 864,  "Greater Striking", "+4 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 10 },
                        EnchantDefinition{ 943,  "Striking", "+3 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 241,  "Lesser Striking", "+2 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 250,  "Minor Striking", "+1 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 854,  "Lesser Elemental Slayer", "+6 Weapon Damage to Elementals", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 190,  "Lesser Beastslayer", "+6 Weapon Damage to Beasts", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 188,  "Minor Beastslayer", "+2 Weapon Damage to Beasts", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_1H_Melee_Offhand),
                    .name = "Offhand",
                    .icon = "inv_weapon_shortblade_03",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2564, "Agility", "+15 Agility", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 2563, "Strength", "+15 Strength", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 1900, "Crusader", "", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1894, "Icy Weapon", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 803,  "Fiery Weapon", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1897, "Superior Striking", "+5 Weapon Damage", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 25 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 864,  "Greater Striking", "+4 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 10 },
                        EnchantDefinition{ 943,  "Striking", "+3 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 241,  "Lesser Striking", "+2 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 250,  "Minor Striking", "+1 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 854,  "Lesser Elemental Slayer", "+6 Weapon Damage to Elementals", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 190,  "Lesser Beastslayer", "+6 Weapon Damage to Beasts", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 188,  "Minor Beastslayer", "+2 Weapon Damage to Beasts", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_2H_Melee),
                    .name = "Two-Handed Melee",
                    .icon = "inv_axe_09",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2646, "Agility", "+25 Agility", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 2, 200 },
                        EnchantDefinition{ 1900, "Crusader", "", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1894, "Icy Weapon", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 803,  "Fiery Weapon", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1896, "Superior Impact", "+9 Weapon Damage", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 15 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 963,  "Greater Impact", "+7 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 10 },
                        EnchantDefinition{ 1897, "Impact", "+5 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 943,  "Lesser Impact", "+3 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 241,  "Minor Impact", "+2 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_1H_Caster),
                    .name = "One-Handed Caster",
                    .icon = "inv_weapon_shortblade_37",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2505, "Healing Power", "+55 Healing power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 2332, "Spell Power", "+30 Spell power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1124, "Mighty Intellect", "+22 Intellect", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 100 },
                        EnchantDefinition{ 2567, "Mighty Spirit", "+20 Spirit", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 100 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 2443, "Winter’s Might", "+7 Frost spell power", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_2H_Caster),
                    .name = "Two-Handed Caster",
                    .icon = "inv_staff_13",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2505, "Healing Power", "+55 Healing power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 2332, "Spell Power", "+30 Spell power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1903, "Major Spirit", "+9 Spirit", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 15 },
                        EnchantDefinition{ 1901, "Major Intellect", "+9 Intellect", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 15 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 255,  "Lesser Spirit", "+3 Spirit", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 723,  "Lesser Intellect", "+3 Spirit", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_Ranged),
                    .name = "Ranged Weapons",
                    .icon = "inv_weapon_bow_11",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2523, "Biznicks 247x128 Accurascope", "+3 Ranged Hit", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 100 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 43,   "Sniper Scope", "+7 Weapon Damage", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 953,  "Deadly Scope", "+5 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 3 },
                        EnchantDefinition{ 33,   "Accurate Scope", "+3 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 2 },
                        EnchantDefinition{ 32,   "Standard Scope", "+2 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 2 },
                        EnchantDefinition{ 30,   "Crude Scope", "+1 Weapon Damage", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 1 }
                        // --- VANILLA END ---
                    }
                }
            }
        },
        EnchantCategoryDefinition {
            .enchantCategoryId = static_cast<uint32>(EnchantCategory::Armor),
            .name = "Armor enchants",
            .icon = "inv_chest_plate05",
            .subTypes = {
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Chest),
                    .name = "Chest",
                    .icon = "inv_chest_plate05",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 1891, "Greater Stats", "+4 All Stats", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 928,  "Stats", "+3 All Stats", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1892, "Major Health", "+100 Health", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1893, "Major Mana", "+100 Mana", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 866,  "Lesser Stats", "+2 All Stats", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 847,  "Minor Stats", "+1 All Stats", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 908,  "Superior Health", "+50 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 850,  "Greater Health", "+35 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 254,  "Health", "+25 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 242,  "Lesser Health", "+15 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 41,   "Minor Health", "+5 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 913,  "Superior Mana", "+65 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 857,  "Greater Mana", "+50 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 843,  "Mana", "+30 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 246,  "Lesser Mana", "+20 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 24,   "Minor Mana", "+5 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 63,   "Lesser Absorption", "", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 44,   "Minor Absorption", "", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Helm),
                    .name = "Helm",
                    .icon = "inv_helmet_13",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2588, "Presence of Sight", "+18 Spell Power + & +1% Spell Hit", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_MAGE), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2590, "Prophetic Aura", "+10 Stamina, 4 MP5 & 24 Healing Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_PRIEST), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2589, "Hoodoo Hex", "+10 Stamina & +18 Spell Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_WARLOCK), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2591, "Animist’s Caress", "+10 Stamina, +10 Intellect & +18 Healing Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_DRUID), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2585, "Death’s Embrace", "+28 Attack Power & +1% Dodge", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_ROGUE), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2586, "Falcon’s Call", "+24 Ranged Attack Power, +10 Stamina & +1% Hit", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_HUNTER), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2587, "Vodouisant’s Vigilant Embrace", "+15 Intellect & +13 Spell Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_SHAMAN), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2584, "Syncretist’s Sigil", "+10 Stamina, +7 Defense & +24 Healing Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_PALADIN), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2583, "Presence of Might", "+10 Stamina, +7 Defense & +15 Shield Block", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_WARRIOR), 0, 0, 60, 2, 150 },
                        EnchantDefinition{ 1508, "Lesser Arcanum of Voracity", "+8 Agility", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1506, "Lesser Arcanum of Voracity", "+8 Strength", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1509, "Lesser Arcanum of Voracity", "+8 Intellect", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1510, "Lesser Arcanum of Voracity", "+8 Spirit", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1507, "Lesser Arcanum of Voracity", "+8 Stamina", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1390, "Savage Guard", "+10 Nature Resistance", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1503, "Lesser Arcanum of Constitution", "+100 Health", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1505, "Lesser Arcanum of Resilience", "+20 Fire Resistance", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1483, "Lesser Arcanum of Rumination", "+150 Mana", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1504, "Lesser Arcanum of Tenacity", "+125 Armor", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 3646, "Arcanum of Protection", "+1% Dodge", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 2544, "Arcanum of Focus", "+Spell Power", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 2543, "Arcanum of Rapidity", "+1% Haste", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Shoulders),
                    .name = "Shoulders",
                    .icon = "inv_shoulder_28",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2606, "Zandalar Signet of Might", "+30 Attack Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 2, 200 },
                        EnchantDefinition{ 2604, "Zandalar Signet of Mojo", "+18 Spell Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 2, 200 },
                        EnchantDefinition{ 2605, "Zandalar Signet of Serenity", "+24 Healing Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 2, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 3242, "Chromatic Mantle of the Dawn", "+5 Resistance", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 2, 50 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Cloak),
                    .name = "Cloak",
                    .icon = "inv_misc_cape_20",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 910,  "Stealth", "Increase to stealth", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 5, 200 },
                        EnchantDefinition{ 2622, "Dodge", "+1% Dodge", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 5, 200 },
                        EnchantDefinition{ 2619, "Greater Fire Resistance", "+15 Fire Resistance", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 2620, "Greater Nature Resistance", "+15 Nature Resistance", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 804,  "Lesser Shadow Resistance", "+10 Shadow Resistance", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1888, "Greater Resistance", "+5 Resistance", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 2621, "Subtlety", "-2% Threat", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 100 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 2463, "Fire Resistance", "+7 Fire Resistance", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1899, "Superior Defense", "+70 Armor", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 884,  "Greater Defense", "+50 Armor", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 849,  "Lesser Agility", "+3 Agility", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 247,  "Minor Agility", "+1 Agility", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 256,  "Lesser Fire Resistance", "+5 Fire Resistance", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 9 },
                        EnchantDefinition{ 903,  "Resistance", "+3 Resistance", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 65,   "Minor Resistance", "+1 Resistance", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 848,  "Defense", "+30 Armor", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 7 },
                        EnchantDefinition{ 744,  "Lesser Protection", "+20 Armor", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 7 },
                        EnchantDefinition{ 783,  "Minor Protection", "+10 Armor", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Chest),
                    .name = "Chest",
                    .icon = "inv_chest_plate05",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 1891, "Greater Stats", "+4 All Stats", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 150 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 928,  "Stats", "+3 All Stats", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1892, "Major Health", "+100 Health", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 1893, "Major Mana", "+100 Mana", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 866,  "Lesser Stats", "+2 All Stats", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 847,  "Minor Stats", "+1 All Stats", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 908,  "Superior Health", "+50 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 850,  "Greater Health", "+35 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 254,  "Health", "+25 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 242,  "Lesser Health", "+15 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 41,   "Minor Health", "+5 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 913,  "Superior Mana", "+65 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 857,  "Greater Mana", "+50 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 843,  "Mana", "+30 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 246,  "Lesser Mana", "+20 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 24,   "Minor Mana", "+5 Mana", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 63,   "Lesser Absorption", "", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 44,   "Minor Absorption", "", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Bracers),
                    .name = "Bracers",
                    .icon = "inv_bracer_14",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2566, "Healing Power", "+24 Healing Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 2565, "Mana Regeneration", "+4 MP5", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 1883, "Greater Intellect", "+7 Intellect", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 1885, "Superior Strength", "+9 Strength", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 1884, "Superior Spirit", "+9 Spirit", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 1886, "Superior Stamina", "+9 Stamina", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 929,  "Greater Stamina", "+7 Stamina", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 927,  "Greater Strength", "+7 Strength", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 907,  "Greater Spirit", "+7 Spirit", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 905,  "Intellect", "+5 Intellect", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 856,  "Strength", "+5 Strength", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 247,  "Minor Agility", "+1 Agility", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 923,  "Deflection", "+3 Defense", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 925,  "Lesser Deflection", "+2 Defense", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 924,  "Minor Deflect", "+1 Defense", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 41,   "Minor Health", "+5 Health", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 66,   "Minor Stamina", "+1 Stamina", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 724,  "Lesser Stamina", "+3 Stamina", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 852,  "Stamina", "+5 Stamina", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 243,  "Minor Spirit", "+1 Spirit", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 255,  "Lesser Spirit", "+3 Spirit", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 851,  "Spirit", "+5 Spirit", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 248,  "Minor Strength", "+1 Strength", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 823,  "Lesser Strength", "+3 Strength", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 723,  "Lesser Intellect", "+3 Intellect", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Gloves),
                    .name = "Gloves",
                    .icon = "inv_gauntlets_24",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2617, "Healing Power", "+30 Healing Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 5, 200 },
                        EnchantDefinition{ 2614, "Shadow Power", "+20 Shadow Spell Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 5, 200 },
                        EnchantDefinition{ 2615, "Frost Power", "+20 Frost Spell Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 5, 200 },
                        EnchantDefinition{ 2616, "Fire Power", "+20 Fire Spell Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 5, 200 },
                        EnchantDefinition{ 2564, "Superior Agility", "+15 Agility", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 5, 200 },
                        EnchantDefinition{ 1887, "Greater Agility", "+7 Agility", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 2613, "Threat", "+2% Threat", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 5, 200 },
                        EnchantDefinition{ 927,  "Greater Strength", "+7 Strength", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 931,  "Minor Haste", "+1% Melee Haste", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 930,  "Riding Skill", "", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 865,  "Skinning", "+5 Skinning", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 906,  "Advanced Mining", "+5 Mining", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 909,  "Advanced Herbalism", "+5 Herbalism", EnchantTier::PreRaid, "Herbalism", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 904,  "Agility", "+5 Agility", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 856,  "Strength", "+5 Strength", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 845,  "Herbalism", "+2 Herbalism", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 846,  "Fishing", "+2 Fishing", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 844,  "Mining", "+2 Mining", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Legs),
                    .name = "Legs",
                    .icon = "inv_pants_06",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 2588, "Presence of Sight", "+18 Spell Power + & +1% Spell Hit", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_MAGE), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2590, "Prophetic Aura", "+10 Stamina, 4 MP5 & 24 Healing Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_PRIEST), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2589, "Hoodoo Hex", "+10 Stamina & +18 Spell Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_WARLOCK), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2591, "Animist’s Caress", "+10 Stamina, +10 Intellect & +18 Healing Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_DRUID), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2585, "Death’s Embrace", "+28 Attack Power & +1% Dodge", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_ROGUE), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2586, "Falcon’s Call", "+24 Ranged Attack Power, +10 Stamina & +1% Hit", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_HUNTER), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2587, "Vodouisant’s Vigilant Embrace", "+15 Intellect & +13 Spell Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_SHAMAN), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2584, "Syncretist’s Sigil", "+10 Stamina, +7 Defense & +24 Healing Power", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_PALADIN), 0, 0, 60, 2, 200 },
                        EnchantDefinition{ 2583, "Presence of Might", "+10 Stamina, +7 Defense & +15 Shield Block", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_WARRIOR), 0, 0, 60, 2, 150 },
                        EnchantDefinition{ 1508, "Lesser Arcanum of Voracity", "+8 Agility", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1506, "Lesser Arcanum of Voracity", "+8 Strength", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1509, "Lesser Arcanum of Voracity", "+8 Intellect", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1510, "Lesser Arcanum of Voracity", "+8 Spirit", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1507, "Lesser Arcanum of Voracity", "+8 Stamina", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 1390, "Savage Guard", "+10 Nature Resistance", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1503, "Lesser Arcanum of Constitution", "+100 Health", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1505, "Lesser Arcanum of Resilience", "+20 Fire Resistance", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1483, "Lesser Arcanum of Rumination", "+150 Mana", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 1504, "Lesser Arcanum of Tenacity", "+125 Armor", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 3646, "Arcanum of Protection", "+1% Dodge", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 2544, "Arcanum of Focus", "+Spell Power", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 },
                        EnchantDefinition{ 2543, "Arcanum of Rapidity", "+1% Haste", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 0, 0, 2, 50 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Boots),
                    .name = "Boots",
                    .icon = "inv_boots_plate_09",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 1887, "Greater Agility", "+7 Agility", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 929,  "Greater Stamina", "+7 Stamina", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 911,  "Minor Speed", "", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 851,  "Spirit", "+5 Spirit", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 852,  "Stamina", "+5 Stamina", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },
                        EnchantDefinition{ 904,  "Agility", "+5 Agility", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 724,  "Lesser Stamina", "+3 Stamina", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 66,   "Minor Stamina", "+1 Stamina", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 849,  "Lesser Agility", "+3 Agility", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 247,  "Minor Agility", "+1 Agility", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Ring_Slot1),
                    .name = "Ring",
                    .icon = "inv_jewelry_ring_22",
                    .enchants = { }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Ring_Slot2),
                    .name = "Ring",
                    .icon = "inv_jewelry_ring_22",
                    .enchants = { }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Subtype_Shield),
                    .name = "Shield",
                    .icon = "inv_shield_10",
                    .enchants = {
                        // --- VANILLA ---
                        // --- RAID TIER ---
                        EnchantDefinition{ 1890, "Superior Spirit", "+9 Spirit", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 929,  "Greater Stamina", "+7 Stamina", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },
                        EnchantDefinition{ 926,  "Frost Resistance", "+8 Frost Res", EnchantTier::Raid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 200 },

                        // --- PRE-RAID TIER ---
                        EnchantDefinition{ 907,  "Greater Spirit", "+7 Spirit", EnchantTier::PreRaid, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 50 },

                        // --- LEVELING TIER ---
                        EnchantDefinition{ 852,  "Stamina", "+5 Stamina", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 724,  "Lesser Stamina", "+3 Stamina", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 66,   "Minor Stamina", "+1 Stamina", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 851,  "Spirit", "+5 Spirit", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 255,  "Lesser Spirit", "+3 Spirit", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 848,  "Lesser Protection", "+30 Armor", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 },
                        EnchantDefinition{ 863,  "Lesser Block", "+2% Block", EnchantTier::Leveling, "", static_cast<uint32>(Classes::CLASS_NONE), 0, 1, 1, 1, 5 }
                        // --- VANILLA END ---
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
            return enchantIt->second.price;
        }
    }

    // Calculate fresh price if not found or expired
    uint32 finalPrice = PriceHelper::GetEnchantPriceInGold(player, enchantDef, subCatId);
    m_playerPriceCache[playerGuid][enchantId] = { finalPrice, now };

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
