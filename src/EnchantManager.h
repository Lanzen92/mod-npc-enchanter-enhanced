/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

#pragma once

#include "Define.h"
#include <string>
#include <vector>

#include "Player.h"

enum EnchantCategory : uint32 {
    Weapon = 1,
    Armor  = 2,
};

enum EnchantSubCategory : uint32 {
    Weapon_1H_Melee = 0,
    Weapon_1H_Melee_Offhand = 1,
    Weapon_2H_Melee = 2,
    Weapon_Ranged = 3,
    Weapon_1H_Caster = 4,
    Weapon_2H_Caster = 5,

    Subtype_Shield = 8,

    Armor_Helm = 10,
    Armor_Shoulders = 11,
    Armor_Cloak = 12,
    Armor_Chest = 13,
    Armor_Waist = 14,
    Armor_Bracers = 15,
    Armor_Gloves = 16,
    Armor_Legs = 17,
    Armor_Boots = 18,
    Armor_Ring_Slot1 = 19,
    Armor_Ring_Slot2 = 20,
};

enum class EnchantTier : uint32 {
    Leveling = 1,
    PreRaid  = 2,
    Raid     = 3
};

struct EnchantDefinition {
    uint32 enchantId;
    std::string name;
    std::string description;
    EnchantTier tier;
    std::string professionRequirement;
    uint32 professionSkillRequirement;
    uint32 reputationRequirement;
    uint32 reputationLevelRequirement;
    uint32 classRequirement;
    uint32 minItemLevel;
    uint32 levelRequirement;
    uint32 phase;
    uint32 cost;
};

struct EnchantSubCategoryDefinition {
    uint32 enchantCategorySubTypeId;
    std::string name;
    std::string icon;
    std::vector<EnchantDefinition> enchants;
};

struct EnchantCategoryDefinition {
    uint32 enchantCategoryId;
    std::string name;
    std::string icon;
    std::vector<EnchantSubCategoryDefinition> subTypes;
};

struct CachedEnchantPriceData
{
    uint32 price;
    uint64 itemGuid;
    std::chrono::steady_clock::time_point timestamp;
};

class NPCEnchanterEnhancedEnchantManager
{
public:
    static NPCEnchanterEnhancedEnchantManager* instance();
    const std::vector<EnchantCategoryDefinition>& GetEnchantDatabase() const;
    const EnchantDefinition* GetEnchantDefinition(uint32 enchantId) const;
    bool SubCategoryHasNoEnchants(uint32 subCategoryId) const;
    bool AllEnchantsInSubCategoryHasProfessionRequirements(uint32 subCategoryId) const;
    std::string GetProfessionLockedPhrase(uint32 subCategoryId) const;

    //CachedEnchantPriceData methods
    uint32 GetOrCacheEnchantPrice(const Player* player, const EnchantDefinition* enchantDef, uint32 subCatId);
    void ClearPlayerPriceCache(uint32 playerGuid);
    void ClearAllPlayerPriceCaches();

private:
    NPCEnchanterEnhancedEnchantManager();
    std::vector<EnchantCategoryDefinition> m_enchantDatabase;
    std::unordered_map<uint32, std::unordered_map<uint32, CachedEnchantPriceData>> m_playerPriceCache;
};

#define sEnchantManager NPCEnchanterEnhancedEnchantManager::instance()

