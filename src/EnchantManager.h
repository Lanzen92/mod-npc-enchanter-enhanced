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
    Armor_Waist = 34,
    Armor_Bracers = 35,
    Armor_Gloves = 36,
    Armor_Legs = 37,
    Armor_Boots = 38,
    Armor_Ring_Slot1 = 39,
    Armor_Ring_Slot2 = 40,
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

