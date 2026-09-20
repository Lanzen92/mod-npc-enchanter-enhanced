/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

#pragma once

#include <string>
#include "Define.h"
#include "SharedDefines.h"
#include "Player.h"
#include "EnchantManager.h"
#include "ValidationHelper.h"

//Get SkillType from string. - This should prob be changed to uint in the enchantDef.
inline SkillType GetProfessionSkillTypeFromString(const std::string& profName)
{
    if (profName == "Enchanting")   return SKILL_ENCHANTING;
    if (profName == "Engineering")  return SKILL_ENGINEERING;
    if (profName == "Blacksmith") return SKILL_BLACKSMITHING;
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

// Get EQUIPMENT_SLOT from SubCategory
inline EquipmentSlots GetEquipmentSlotFromSubCategory(uint32 subCat)
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

enum ProgressionAchievements
{
    KEL_THUZAD_40_KILL   = 533, // Vanilla
    KEL_THUZAD_KILL      = 575, // WotLK
    ONYXIA_KILL          = 684,
    NEFARIAN_KILL        = 685,
    RAGNAROS_KILL        = 686,
    C_THUN_KILL          = 687,
    MALCHEZAAR_KILL      = 690,
    ZUL_JIN_KILL         = 691,
    KAEL_THAS_KILL       = 696,
    ILLIDAN_KILL         = 697,
    KIL_JAEDEN_KILL      = 698,
    ANUB_ARAK_KILL       = 3916,
    LICH_KING_KILL       = 4597,
    HALION_KILL          = 4815
};

enum ProgressionQuests
{
    PRE_AQ_WAR_EFFORT    = 8743, //Bang a Gong!
    AQ_OPENING           = 108744, // Chaos and Destruction
    TBC_PRE_OPENING          = 10259, //Into the Breach
};

static const std::vector<std::pair<uint8, uint32>> bossProgression =
{
    /* Phase, Achievement */
    { 0,  RAGNAROS_KILL     }, // 686
    { 1,  ONYXIA_KILL       }, // 684
    { 2,  NEFARIAN_KILL     }, // 685
    { 5,  C_THUN_KILL       }, // 687
    { 8,  MALCHEZAAR_KILL   }, // 690
    { 9,  KAEL_THAS_KILL    }, // 696
    { 10, ILLIDAN_KILL      }, // 697
    { 12, KIL_JAEDEN_KILL   }, // 698
    { 13, KEL_THUZAD_KILL   }, // 575
    { 15, ANUB_ARAK_KILL    }, // 3916
    { 16, LICH_KING_KILL    }, // 4597
    { 17, HALION_KILL       }, // 4815
};

static const std::vector<std::pair<uint8, uint32>> questProgression =
{
    /* Phase, Achievement */
    { 3,  PRE_AQ_WAR_EFFORT     }, // 8743
    { 4,  AQ_OPENING            }, // 108744
    { 7,  TBC_PRE_OPENING       }, // 10259
};

struct ExpansionPhaseBracket
{
    std::string expansionName;
    uint8 minPhase;
    uint8 maxPhase;
};

static const std::vector<ExpansionPhaseBracket> expansionBrackets =
{
    { "VANILLA", 1,  7  },
    { "TBC",     8,  12 },
    { "WOTLK",   13, 25 }
};

//Returns the questId for phase
inline uint32 GetQuestForPhase(uint8 targetPhase)
{
    auto it = std::ranges::find_if(questProgression, [targetPhase](const auto& pair) {
        return pair.first == targetPhase;
    });

    return (it != questProgression.end()) ? it->second : 0;
}

//Get Individualprogression phase.
inline uint32 GetPlayerPhase(const Player* player)
{
    uint32 currentPhase = 1;

    //Check for boss kills
    for (auto const& [bossKillProgressionId, achievementId] : bossProgression)
    {
        if (player->HasAchieved(achievementId) && bossKillProgressionId > currentPhase)
        {
            currentPhase = bossKillProgressionId;

            //Check for quest completion to know if phase 3, 4 or 7.
            if (currentPhase == 2 && player->GetQuestStatus(GetQuestForPhase(currentPhase + 1)))
            {
                currentPhase = bossKillProgressionId + 1;
            }
            if (currentPhase == 3 && player->GetQuestStatus(GetQuestForPhase(currentPhase + 1)))
            {
                currentPhase = bossKillProgressionId + 1;
            }
            if (currentPhase == 6 && player->GetQuestStatus(GetQuestForPhase(currentPhase + 1)))
            {
                currentPhase = bossKillProgressionId + 1;
            }
        }
    }

    return currentPhase;
}

// Helper function to get the expansion tier ID for any given phase
inline uint8 GetExpansionForPhase(uint32 phase)
{
    for (size_t i = 0; i < expansionBrackets.size(); ++i)
    {
        if (phase >= expansionBrackets[i].minPhase && phase <= expansionBrackets[i].maxPhase)
        {
            return static_cast<uint8>(i); // 0 = Vanilla, 1 = TBC, 2 = WotLK
        }
    }
    return 0;
}

inline std::string GetExpansionNameForPhase(uint32 phase)
{
    for (size_t i = 0; i < expansionBrackets.size(); ++i)
    {
        if (phase >= expansionBrackets[i].minPhase && phase <= expansionBrackets[i].maxPhase)
        {
            return expansionBrackets[i].expansionName;
        }
    }
    return "Unknown";
}

inline std::string ToLower(std::string str)
{
    std::ranges::transform(str, str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return str;
}
