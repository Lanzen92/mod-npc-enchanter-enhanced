#include "PriceHelper.h"

#include "CommonHelper.h"
#include "ConfigManager.h"
#include "Define.h"
#include "EnchantManager.h"

uint32 PriceHelper::GetEnchantPriceInGold(const Player* player, const EnchantDefinition* enchantDef, uint32 subCatId)
{
    if (!NPCEnchanterEnhancedDynamicPricesOnEnchants)
        return enchantDef->cost;

    //Dynamic price
    return CalculateDynamicEnchantPrice(enchantDef, player, subCatId);
}

//Adjust price according to itemlevel, level
uint32 PriceHelper::CalculateDynamicEnchantPrice(const EnchantDefinition* enchantDef, const Player* player, uint32 subCatId)
{
    // Initialize basePrice with a safe default fallback
    uint32 basePrice;
    float qualityMultiplier = NPCEnchanterEnhancedQualityMultiplierNormal;
    float variancePercentage = NPCEnchanterEnhancedVariancePercentage;

    EquipmentSlots targetSlot = GetEquipmentSlotFromSubCategory(subCatId);
    Item* targetItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, targetSlot);

    uint32 itemLevel = targetItem->GetTemplate()->ItemLevel;
    uint32 itemQuality = targetItem->GetTemplate()->Quality; // Keep as uint32
    uint32 playerLevel = player->GetLevel();

    // Tier base costs
    switch (enchantDef->tier)
    {
        case EnchantTier::Leveling:     basePrice = NPCEnchanterEnhancedBasePriceLeveling; break;
        case EnchantTier::PreRaid:      basePrice = NPCEnchanterEnhancedBasePricePreRaid; break;
        case EnchantTier::Raid:         basePrice = NPCEnchanterEnhancedBasePriceRaid; break;
        default:                        basePrice = NPCEnchanterEnhancedBasePriceLeveling; break;
    }

    // Item Quality Modifier
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

    //Multiply by itemLevel and player level
    float itemLevelAdjustment = static_cast<float>(itemLevel) * NPCEnchanterEnhancedItemLevelMultiplier;
    float playerLevelAdjustment = static_cast<float>(playerLevel) * NPCEnchanterEnhancedPlayerLevelMultiplier;

    LOG_INFO("server.loading", "CalculateDynamicEnchantPrice itemLevelAdjustment {}, playerLevelAdjustment {},", itemLevelAdjustment, playerLevelAdjustment);

    // 1. Calculate base subtotal and multiply by quality modifier
    float adjustedPrice = (static_cast<float>(basePrice) + itemLevelAdjustment + playerLevelAdjustment) * qualityMultiplier;

    LOG_INFO("server.loading", "CalculateDynamicEnchantPrice adjustedPrice {}", adjustedPrice);

    // 2. Variance multiplier
    if (variancePercentage > 0.0f)
    {
        float minMultiplier = 1.0f - variancePercentage;
        float maxMultiplier = 1.0f + variancePercentage;

        adjustedPrice *= frand(minMultiplier, maxMultiplier);
    }

    LOG_INFO("server.loading", "CalculateDynamicEnchantPrice after variance adjustedPrice {}", adjustedPrice);
    return static_cast<uint32>(adjustedPrice);
}
