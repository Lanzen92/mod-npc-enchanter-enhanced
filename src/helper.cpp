#include "helper.h"

#include "ConfigManager.h"
#include "Define.h"
#include "EnchantManager.h"


const uint32 GetEnchantPriceInGold (const EnchantDefinition* enchantDef)
{
    if (!NPCEnchanterEnhancedDynamicPricesOnEnchants)
        return enchantDef->cost;

    //Implement dynamic prices here :)

    return enchantDef->cost;
}

const uint32 GetEnchantPriceInCopper (const EnchantDefinition* enchantDef)
{
    if (!NPCEnchanterEnhancedDynamicPricesOnEnchants)
        return GOLD(enchantDef->cost);

    //Implement dynamic prices here :)

    return GOLD(enchantDef->cost);
}


