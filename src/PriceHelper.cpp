#include "PriceHelper.h"

#include "ConfigManager.h"
#include "Define.h"
#include "EnchantManager.h"

uint32 PriceHelper::GetEnchantPriceInGold (const EnchantDefinition* enchantDef)
{
    if (!NPCEnchanterEnhancedDynamicPricesOnEnchants)
        return enchantDef->cost;

    //Implement dynamic prices here :)

    return enchantDef->cost;
}

uint32 PriceHelper::GetEnchantPriceInCopper (const EnchantDefinition* enchantDef)
{
    if (!NPCEnchanterEnhancedDynamicPricesOnEnchants)
        return GOLD(enchantDef->cost);

    //Implement dynamic prices here :)

    return GOLD(enchantDef->cost);
}
