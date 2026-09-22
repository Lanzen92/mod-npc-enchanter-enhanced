/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

#include "PriceHelper.h"

#include "CommonHelper.h"
#include "ConfigManager.h"
#include "Define.h"
#include "EnchantManager.h"

uint32 PriceHelper::GetEnchantPriceInGold(const Player* player, const EnchantDefinition* enchantDef, uint32 subCatId)
{
    if (!NPCEnchanterEnhancedDynamicPricesOnEnchants)
        return enchantDef->cost;

    if (NPCEnchanterEnhancedFreeEnchants)
        return 0;

    //Dynamic price
    return CalculateDynamicEnchantPrice(enchantDef, player, subCatId);
}

//Adjust price according to itemlevel, level
uint32 PriceHelper::CalculateDynamicEnchantPrice(const EnchantDefinition* enchantDef, const Player* player, uint32 subCatId)
{
    if (!enchantDef || !player)
        return 0;

    uint32 basePrice = NPCEnchanterEnhancedBasePriceLeveling;
    float qualityMultiplier = NPCEnchanterEnhancedQualityMultiplierNormal;
    float variancePercentage = NPCEnchanterEnhancedVariancePercentage;

    // 1. Fetch Item Safely
    EquipmentSlots targetSlot = GetEquipmentSlotFromSubCategory(subCatId);
    Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, targetSlot);

    uint32 itemLevel = targetItem ? targetItem->GetTemplate()->ItemLevel : 1;
    uint32 itemQuality = targetItem ? targetItem->GetTemplate()->Quality : ITEM_QUALITY_NORMAL;
    uint32 playerLevel = player->GetLevel();

    // 2. Tier base costs
    switch (enchantDef->tier)
    {
        case EnchantTier::Leveling:     basePrice = NPCEnchanterEnhancedBasePriceLeveling; break;
        case EnchantTier::PreRaid:      basePrice = NPCEnchanterEnhancedBasePricePreRaid; break;
        case EnchantTier::Raid:         basePrice = NPCEnchanterEnhancedBasePriceRaid; break;
        default:                        basePrice = NPCEnchanterEnhancedBasePriceLeveling; break;
    }

    // 3. Item Quality Modifier
    switch (itemQuality)
    {
        case ITEM_QUALITY_NORMAL:       qualityMultiplier = NPCEnchanterEnhancedQualityMultiplierNormal; break;
        case ITEM_QUALITY_UNCOMMON:     qualityMultiplier = NPCEnchanterEnhancedQualityMultiplierUncommon; break;
        case ITEM_QUALITY_HEIRLOOM:
        case ITEM_QUALITY_RARE:         qualityMultiplier = NPCEnchanterEnhancedQualityMultiplierRare; break;
        case ITEM_QUALITY_EPIC:         qualityMultiplier = NPCEnchanterEnhancedQualityMultiplierEpic; break;
        case ITEM_QUALITY_ARTIFACT:
        case ITEM_QUALITY_LEGENDARY:    qualityMultiplier = NPCEnchanterEnhancedQualityMultiplierLegendary; break;
        default: break;
    }

    // 4. Scale adjustments using your config multipliers
    float itemLevelAdjustment = static_cast<float>(itemLevel) * NPCEnchanterEnhancedItemLevelMultiplier;
    float playerLevelAdjustment = static_cast<float>(playerLevel) * NPCEnchanterEnhancedPlayerLevelMultiplier;

    // 5. Multiplicative scaling across expansions
    float adjustedPrice = static_cast<float>(basePrice)
                        * (1.0f + itemLevelAdjustment)
                        * (1.0f + playerLevelAdjustment)
                        * qualityMultiplier;

    // 6. Variance Multiplier
    if (variancePercentage > 0.0f)
    {
        float minMultiplier = 1.0f - variancePercentage;
        float maxMultiplier = 1.0f + variancePercentage;
        adjustedPrice *= frand(minMultiplier, maxMultiplier);
    }

    return static_cast<uint32>(adjustedPrice);
}
