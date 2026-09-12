#pragma once

#include "EnchantManager.h"

#define COPPER(n) ((uint64)(n))
#define SILVER(n) (COPPER(n) * 100)
#define GOLD(n)   (SILVER(n) * 100)

const uint32 GetEnchantPriceInCopper (const EnchantDefinition* enchantDef);
const uint32 GetEnchantPriceInGold (const EnchantDefinition* enchantDef);
