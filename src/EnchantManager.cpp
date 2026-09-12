#include "EnchantManager.h"
#include <string>


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
                        EnchantDefinition{ 1900, "Crusader", EnchantTier::Raid, "", 0, 0, 0, 1, 150 },
                        EnchantDefinition{ 2563, "Strength (+15 Strength)", EnchantTier::Raid, "", 0, 0, 0, 5, 200 },
                        EnchantDefinition{ 2564, "Agility (+15 Agility)", EnchantTier::Raid, "", 0, 0, 0, 5, 200 },
                        EnchantDefinition{ 803,  "Fiery Weapon", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1894, "Icy Weapon", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1897, "Superior Striking (+5 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 10 },
                        EnchantDefinition{ 864,  "Greater Striking (+4 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 10 },
                        EnchantDefinition{ 943,  "Striking (+3 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 241,  "Lesser Striking (+2 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 250,  "Minor Striking (+1 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 854,  "Lesser Elemental Slayer", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 190,  "Lesser Beastslayer", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 188,  "Minor Beastslayer", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 }
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_1H_Melee_Offhand),
                    .name = "Offhand",
                    .icon = "inv_weapon_shortblade_03",
                    .enchants = {
                        EnchantDefinition{ 1900, "Crusader", EnchantTier::Raid, "", 0, 0, 0, 1, 150 },
                        EnchantDefinition{ 2563, "Strength (+15 Strength)", EnchantTier::Raid, "", 0, 0, 0, 5, 200 },
                        EnchantDefinition{ 2564, "Agility (+15 Agility)", EnchantTier::Raid, "", 0, 0, 0, 5, 200 },
                        EnchantDefinition{ 803,  "Fiery Weapon", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1894, "Icy Weapon", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1897, "Superior Striking (+5 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 10 },
                        EnchantDefinition{ 864,  "Greater Striking (+4 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 10 },
                        EnchantDefinition{ 943,  "Striking (+3 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 241,  "Lesser Striking (+2 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 250,  "Minor Striking (+1 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 854,  "Lesser Elemental Slayer", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 190,  "Lesser Beastslayer", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 188,  "Minor Beastslayer", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 }
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_2H_Melee),
                    .name = "Two-Handed Melee",
                    .icon = "inv_axe_09",
                    .enchants = {
                        EnchantDefinition{ 1900, "Crusader", EnchantTier::Raid, "", 0, 0, 0, 1, 150 },
                        EnchantDefinition{ 2646, "Agility (+25 Agility)", EnchantTier::Raid, "", 0, 0, 5, 1, 200 },
                        EnchantDefinition{ 803,  "Fiery Weapon", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1899, "Unholy Weapon", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1898, "Lifestealing", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 912,  "Demonslaying", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1894, "Icy Weapon", EnchantTier::PreRaid, "", 0, 0, 0, 1, 50 },
                        EnchantDefinition{ 1896, "Superior Impact (+9 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 15 },
                        EnchantDefinition{ 963,  "Greater Impact (+7 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 10 },
                        EnchantDefinition{ 1897, "Impact (+5 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 943,  "Lesser Impact (+3 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 },
                        EnchantDefinition{ 241,  "Minor Impact (+2 Damage)", EnchantTier::Leveling, "", 0, 0, 0, 1, 5 }
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_1H_Caster),
                    .name = "One-Handed Caster",
                    .icon = "inv_weapon_shortblade_37",
                    .enchants = {
                        EnchantDefinition{ 2505, "Healing Power (+55 Healing Power)", EnchantTier::Raid, "", 0, 0, 0, 1, 200 },
                        EnchantDefinition{ 2332, "Spell Power (+30 Spell Power)", EnchantTier::Raid, "", 0, 0, 0, 5, 200 },
                        EnchantDefinition{ 1124, "Mighty Intellect (+22 Intellect)", EnchantTier::PreRaid, "", 0, 0, 0, 1, 30 },
                        EnchantDefinition{ 2567, "Mighty Spirit (+20 Spirit)", EnchantTier::PreRaid, "", 0, 0, 0, 1, 30 },
                        EnchantDefinition{ 2443, "Winter's Might (+7 Frost Spell Power)", EnchantTier::Leveling, "", 0, 0, 0, 1, 10 }
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_2H_Caster),
                    .name = "Two-Handed Caster",
                    .icon = "inv_staff_13",
                    .enchants = {
                        EnchantDefinition{ 2505, "Healing Power (+55 Healing Power)", EnchantTier::Raid, "", 0, 0, 0, 1,  200 },
                         EnchantDefinition{ 2332, "Spell Power (+30 Spell Power)", EnchantTier::Raid, "", 0, 0, 0, 5,  200 },
                         EnchantDefinition{ 1903, "Major Spirit (+9 Spirit)", EnchantTier::Leveling, "", 0, 0, 0, 1,  15 },
                         EnchantDefinition{ 255,  "Lesser Spirit (+3 Spirit)", EnchantTier::Leveling, "", 0, 0, 0, 1,  5 },
                         EnchantDefinition{ 1901, "Major Intellect (+9 Intellect)", EnchantTier::Leveling, "", 0, 0, 0, 1,  10 },
                         EnchantDefinition{ 723,  "Lesser Intellect (+3 Spirit)", EnchantTier::Leveling, "", 0, 0, 0, 1,  5 }
                    }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Weapon_Ranged),
                    .name = "Ranged Weapons",
                    .icon = "inv_weapon_bow_11",
                    .enchants = {
                        EnchantDefinition{ 2523, "Biznick's 247x128 Accurascope (+3 Hit)", EnchantTier::Raid, "", 200, 0, 35, 1,  150 },
                        EnchantDefinition{ 843,  "Sniper Scope (+7 Damage)",               EnchantTier::PreRaid, "", 150, 0, 25, 1,50 },
                        EnchantDefinition{ 953,  "Deadly Scope (+5 Damage)",               EnchantTier::Leveling, "", 100, 0, 15, 1,10 },
                        EnchantDefinition{ 33,   "Accurate Scope (+3 Damage)",             EnchantTier::Leveling, "", 50,  0, 10, 1,10 },
                        EnchantDefinition{ 32,   "Standard Scope (+2 Damage)",             EnchantTier::Leveling, "", 1,   0,  5, 1,5 },
                        EnchantDefinition{ 30,   "Crude Scope (+1 Damage)",                EnchantTier::Leveling, "", 1,   0,  1, 1, 5 }
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
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Helm),
                    .name = "Helm",
                    .icon = "inv_helmet_13",
                    .enchants = { }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Shoulders),
                    .name = "Shoulders",
                    .icon = "inv_shoulder_28",
                    .enchants = { }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Cloak),
                    .name = "Cloak",
                    .icon = "inv_misc_cape_20",
                    .enchants = { }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Chest),
                    .name = "Chest",
                    .icon = "inv_chest_plate05",
                    .enchants = { }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Bracers),
                    .name = "Bracers",
                    .icon = "inv_bracer_14",
                    .enchants = { }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Gloves),
                    .name = "Gloves",
                    .icon = "inv_gauntlets_24",
                    .enchants = { }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Legs),
                    .name = "Legs",
                    .icon = "inv_pants_06",
                    .enchants = { }
                },
                EnchantSubCategoryDefinition {
                    .enchantCategorySubTypeId = static_cast<uint32>(EnchantSubCategory::Armor_Boots),
                    .name = "Boots",
                    .icon = "inv_boots_plate_09",
                    .enchants = { }
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
                    .enchants = { }
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

//Check if all enchants are locked behind profession, to lock the whole category.
const bool NPCEnchanterEnhancedEnchantManager::AllEnchantsInSubCategoryHasProfessionRequirements(uint32 subCategoryId) const
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
const std::string NPCEnchanterEnhancedEnchantManager::GetProfessionLockedPhrase(uint32 subCategoryId) const
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

                        if (enchant.professionSkillRequirement > professionLowestSkill)
                        {
                            professionLowestSkill = enchant.professionSkillRequirement;
                        }
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
