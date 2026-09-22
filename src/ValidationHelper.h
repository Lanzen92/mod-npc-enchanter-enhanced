/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

#pragma once

#include <string>
#include "CommonHelper.h"

class Player;
struct EnchantDefinition;

struct EnchantValidationResult {
    bool isLocked = false;
    std::string reason = "";
    std::string priceString = "";
    bool showEnchant = true;
};

class ValidationHelper
{
    static bool ValidateEquipment(const Player* player, uint32 subCatId, std::string& reason);
    static bool ValidateProfession(const Player* player, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidateGold(const Player* player, uint32 cost, std::string& reason, std::string& priceString);
    static bool ValidatePhase(uint32 playerPhase, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidateExpansion(const Player* player, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidateLevel(const Player* player, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidateItemLevel(const Player* player, uint32 subCatId, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidateItemRequiredLevel(const Player* player, uint32 subCatId,const EnchantDefinition& enchant, std::string& reason);
    static bool ValidateReputationLevel(const Player* player, const EnchantDefinition& enchant, std::string& reason);
    static bool ValidatePlayerClass(const Player* player, const EnchantDefinition& enchant, std::string& reason);
    static bool FilterTier(const EnchantDefinition& enchant);

public:
    static EnchantValidationResult EvaluateEnchant(const Player* player, uint32 subCatId, const EnchantDefinition& enchant, uint32 enchantCost, uint32 currentPhase);
    static bool ValidateSubCategoryRequirements(const Player* player, const EnchantSubCategoryDefinition& subCat, std::string& reason);
    static bool ValidateSubCategoryEquipment(const Player* player, uint32 subCatId, std::string& reason);
};
