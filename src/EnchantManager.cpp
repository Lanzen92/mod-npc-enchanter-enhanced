#include "EnchantManager.h"

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
                    static_cast<uint32>(EnchantSubCategory::Weapon_1H_Melee),
                    "One-Handed Melee",
                    "inv_sword_39",
                    "",
                    0,
                    0,
                    1,
                    {
                        EnchantDefinition{ 1900, "Crusader", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Raid, "Enchanting", 0, 0, 1, 0, 150 },
                        EnchantDefinition{ 803,  "Fiery Weapon", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 1894, "Icy Weapon", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 2563, "Strength (+15 Strength)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Raid, "Enchanting", 0, 0, 1, 0, 200 },
                        EnchantDefinition{ 2564, "Agility (+15 Agility)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Raid, "Enchanting", 0, 0, 1, 0, 200 },
                        EnchantDefinition{ 1897, "Superior Striking (+5 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 10 },
                        EnchantDefinition{ 864,  "Greater Striking (+4 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 10 },
                        EnchantDefinition{ 943,  "Striking (+3 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 241,  "Lesser Striking (+2 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 250,  "Minor Striking (+1 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 854,  "Lesser Elemental Slayer", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 190,  "Lesser Beastslayer", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 188,  "Minor Beastslayer", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 }
                    }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Weapon_1H_Melee_Offhand),
                    "One-Handed Melee",
                    "inv_weapon_shortblade_03",
                    "",
                    0,
                    0,
                    1,
                    {
                        EnchantDefinition{ 1900, "Crusader", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Raid, "Enchanting", 0, 0, 1, 0, 150 },
                        EnchantDefinition{ 803,  "Fiery Weapon", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 1894, "Icy Weapon", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 50 },
                        EnchantDefinition{ 2563, "Strength (+15 Strength)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Raid, "Enchanting", 0, 0, 1, 0, 200 },
                        EnchantDefinition{ 2564, "Agility (+15 Agility)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Raid, "Enchanting", 0, 0, 1, 0, 200 },
                        EnchantDefinition{ 1897, "Superior Striking (+5 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 10 },
                        EnchantDefinition{ 864,  "Greater Striking (+4 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 10 },
                        EnchantDefinition{ 943,  "Striking (+3 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 241,  "Lesser Striking (+2 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 250,  "Minor Striking (+1 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 854,  "Lesser Elemental Slayer", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 190,  "Lesser Beastslayer", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 188,  "Minor Beastslayer", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 }
                    }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Weapon_2H_Melee),
                    "Two-Handed Melee",
                    "inv_axe_09",
                    "",
                    0,
                    0,
                    1,
                    {
                        EnchantDefinition{ 2646, "Agility (+25 Agility)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Melee, EnchantTier::Raid, "Enchanting", 0, 0, 1, 0, 200 },
                        EnchantDefinition{ 1896, "Superior Impact (+9 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 15 },
                        EnchantDefinition{ 963,  "Greater Impact (+7 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 10 },
                        EnchantDefinition{ 1897, "Impact (+5 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 943,  "Lesser Impact (+3 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 241,  "Minor Impact (+2 Damage)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Melee, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 }
                    }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Weapon_1H_Caster),
                    "One-Handed Caster",
                    "inv_weapon_shortblade_37",
                    "",
                    0,
                    0,
                    1,
                    {
                        EnchantDefinition{ 2505, "Healing Power (+55 Healing Power)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Caster, EnchantTier::Raid, "Enchanting", 0, 0, 1, 0, 200 },
                        EnchantDefinition{ 1124, "Mighty Intellect (+22 Intellect)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Caster, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 100 },
                        EnchantDefinition{ 2567, "Mighty Spirit (+20 Spirit)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Caster, EnchantTier::PreRaid, "Enchanting", 0, 0, 1, 0, 100 },
                        EnchantDefinition{ 2443, "Winter's Might (+7 Frost Spell Power)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Caster, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 2332, "Spell Power (+30 Spell Power)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_1H_Caster, EnchantTier::Raid, "Enchanting", 0, 0, 1, 0, 200 }
                    }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Weapon_2H_Caster),
                    "Two-Handed Caster",
                    "inv_staff_13",
                    "",
                    0,
                    0,
                    1,
                    {
                        EnchantDefinition{ 1903, "Major Spirit (+9 Spirit)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Caster, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 15 },
                        EnchantDefinition{ 255,  "Lesser Spirit (+3 Spirit)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Caster, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 },
                        EnchantDefinition{ 1901, "Major Intellect (+9 Intellect)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Caster, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 10 },
                        EnchantDefinition{ 723,  "Lesser Intellect (+3 Spirit)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_2H_Caster, EnchantTier::Leveling, "Enchanting", 0, 0, 1, 0, 5 }
                    }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Weapon_Ranged),
                    "Ranged Weapons",
                    "inv_weapon_bow_11",
                    "",
                    0,
                    0,
                    1,
                    {
                        EnchantDefinition{ 2523, "Biznick's 247x128 Accurascope (+3 Hit)", EnchantCategory::Weapon, EnchantSubCategory::Weapon_Ranged, EnchantTier::Leveling, "Engineering", 200, 35, 1, 0, 50000 },
                        EnchantDefinition{ 843,  "Sniper Scope (+7 Damage)",                EnchantCategory::Weapon, EnchantSubCategory::Weapon_Ranged, EnchantTier::Leveling, "Engineering", 150, 25, 1, 0, 25000 },
                        EnchantDefinition{ 953,  "Deadly Scope (+5 Damage)",               EnchantCategory::Weapon, EnchantSubCategory::Weapon_Ranged, EnchantTier::Leveling, "Engineering", 100, 15, 1, 0, 10000 },
                        EnchantDefinition{ 33,   "Accurate Scope (+3 Damage)",             EnchantCategory::Weapon, EnchantSubCategory::Weapon_Ranged, EnchantTier::Leveling, "Engineering", 50,  10, 1, 0, 5000  },
                        EnchantDefinition{ 32,   "Standard Scope (+2 Damage)",             EnchantCategory::Weapon, EnchantSubCategory::Weapon_Ranged, EnchantTier::Leveling, "Engineering", 1,   5,  1, 0, 1000  },
                        EnchantDefinition{ 30,   "Crude Scope (+1 Damage)",                EnchantCategory::Weapon, EnchantSubCategory::Weapon_Ranged, EnchantTier::Leveling, "Engineering", 1,   1,  1, 0, 500   }
                    }
                }
            }
        },
        EnchantCategoryDefinition {
            static_cast<uint32>(EnchantCategory::Armor),
            "Armor enchants",
            "inv_chest_plate05",
            {
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Helm),
                    "Helm",
                    "inv_helmet_13",
                    "",
                    0,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Shoulders),
                    "Shoulders",
                    "inv_shoulder_28",
                    "",
                    0,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Cloak),
                    "Cloak",
                    "inv_misc_cape_20",
                    "",
                    0,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Chest),
                    "Chest",
                    "inv_chest_plate05",
                    "",
                    0,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Bracers),
                    "Bracers",
                    "inv_bracer_14",
                    "",
                    0,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Gloves),
                    "Gloves",
                    "inv_gauntlets_24",
                    "",
                    0,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Legs),
                    "Legs",
                    "inv_pants_06",
                    "",
                    0,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Boots),
                    "Boots",
                    "inv_boots_plate_09",
                    "",
                    0,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Ring_Slot1),
                    "Ring",
                    "inv_jewelry_ring_22",
                    "Enchanting",
                    400,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Armor_Ring_Slot2),
                    "Ring",
                    "inv_jewelry_ring_22",
                    "Enchanting",
                    400,
                    0,
                    1,
                    { }
                },
                EnchantSubCategoryDefinition {
                    static_cast<uint32>(EnchantSubCategory::Subtype_Shield),
                    "Shield",
                    "inv_shield_10",
                    "",
                    0,
                    0,
                    1,
                    { }
                }
            }
        }
    };
}

const std::vector<EnchantCategoryDefinition>& NPCEnchanterEnhancedEnchantManager::GetEnchantDatabase() const
{
    return m_enchantDatabase;
}

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
