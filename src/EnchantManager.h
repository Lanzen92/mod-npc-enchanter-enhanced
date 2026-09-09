#ifndef ENCHANT_MANAGER_H
#define ENCHANT_MANAGER_H

#include "Define.h"
#include <string>
#include <vector>

enum EnchantCategory : uint32 {
    Weapon = 1,
    Armor  = 2,
    Shield = 3
};

enum EnchantSubCategory : uint32 {
    Weapon_1H_Melee = 10,
    Weapon_1H_Melee_Offhand = 11,
    Weapon_2H_Melee = 12,
    Weapon_Ranged = 13,
    Weapon_1H_Caster = 14,
    Weapon_2H_Caster = 15,

    Subtype_Shield = 20,

    Armor_Helm = 30,
    Armor_Shoulders = 31,
    Armor_Cloak = 32,
    Armor_Chest = 33,
    Armor_Bracers = 34,
    Armor_Gloves = 35,
    Armor_Legs = 36,
    Armor_Boots = 37,
    Armor_Ring_Slot1 = 38,
    Armor_Ring_Slot2 = 39,
};

enum class EnchantTier : uint32 {
    Leveling = 1,
    PreRaid  = 2,
    Raid     = 3
};

struct EnchantDefinition {
    uint32 enchantId;
    std::string name;
    EnchantCategory category;
    EnchantSubCategory subCategory;
    EnchantTier tier;
    std::string professionRequirement;
    uint32 professionSkillRequirement;
    uint32 minItemLevel;
    uint32 phase;
    uint32 expansion;
    uint32 cost;
};

struct EnchantSubCategoryDefinition {
    uint32 enchantCategorySubTypeId;
    std::string name;
    std::string icon;
    std::string professionRequirement;
    uint32 professionSkillRequirement;
    uint32 minItemLevel;
    uint32 phase;
    std::vector<EnchantDefinition> enchants;
};

struct EnchantCategoryDefinition {
    uint32 enchantCategoryId;
    std::string name;
    std::string icon;
    std::vector<EnchantSubCategoryDefinition> subTypes;
};

class NPCEnchanterEnhancedEnchantManager
{
public:
    static NPCEnchanterEnhancedEnchantManager* instance();

    const std::vector<EnchantCategoryDefinition>& GetEnchantDatabase() const;
    const EnchantDefinition* GetEnchantDefinition(uint32 enchantId) const;

private:
    NPCEnchanterEnhancedEnchantManager();
    std::vector<EnchantCategoryDefinition> m_enchantDatabase;
};

#define sEnchantManager NPCEnchanterEnhancedEnchantManager::instance()

#endif // ENCHANT_MANAGER_H
