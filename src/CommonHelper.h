#pragma once

#include <string>
#include "Define.h"
#include "SharedDefines.h"
#include "Player.h"
#include "EnchantManager.h"

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

inline std::string ToLower(std::string str)
{
    std::ranges::transform(str, str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return str;
}
