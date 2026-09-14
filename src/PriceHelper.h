#pragma once

#include "EnchantManager.h"

#define COPPER(n) ((uint64)(n))
#define SILVER(n) (COPPER(n) * 100)
#define GOLD(n)   (SILVER(n) * 100)


class PriceHelper
{
private:

public:
    static uint32 GetEnchantPriceInCopper (const EnchantDefinition* enchantDef);
    static uint32 GetEnchantPriceInGold (const EnchantDefinition* enchantDef);
};



