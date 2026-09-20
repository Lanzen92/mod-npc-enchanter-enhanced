/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

#pragma once

#include "EnchantManager.h"

// Define currency conversions
#define COPPER(n) ((uint32)(n)) // Convert n to copper
#define SILVER(n) (COPPER(n) * 100) // Convert n to silver
#define GOLD(n)   (SILVER(n) * 100) // Convert n to gold

class PriceHelper
{
private:
    static uint32 CalculateDynamicEnchantPrice (const EnchantDefinition* enchantDef, const Player* player, uint32 subCatId);
public:
    static uint32 GetEnchantPriceInGold (const Player* player, const EnchantDefinition* enchantDef, uint32 subCatId);
};
