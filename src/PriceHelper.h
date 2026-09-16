#pragma once

#include "EnchantManager.h"

// Define currency conversions
#define COPPER(n) ((uint64)(n)) // Convert n to copper
#define SILVER(n) (COPPER(n) * 100) // Convert n to silver
#define GOLD(n)   (SILVER(n) * 100) // Convert n to gold

class PriceHelper
{
private:
    static uint32 CalculateDynamicEnchantPrice (const EnchantDefinition* enchantDef, const Player* player, uint32 subCatId);
public:
    //static uint32 GetEnchantPriceInCopper (const EnchantDefinition* enchantDef);
    static uint32 GetEnchantPriceInGold (const Player* player, const EnchantDefinition* enchantDef, uint32 subCatId);
};



