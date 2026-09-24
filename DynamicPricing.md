# Dynamic Pricing System

The **NPC Enchanter Enhanced** module features a robust, expansion-aware dynamic pricing system. Instead of relying on static gold costs, enchants scale intelligently based on the item's progression tier, item level, player level, and item quality.

This ensures that high-end gear in later expansions naturally commands an appropriate economic value without breaking lower-tier progression.

## Cache

Because the dynamic pricing model uses a random variance ($\pm 15\%$) to give each interaction an organic feel, the calculated price fluctuates slightly. To prevent the price from shifting unpredictably between the time a player views it in the NPC gossip menu and the time they click to purchase it, prices are actively cached.

* **Per-Player, Per-Enchant Keying:** The module stores calculated prices inside an internal memory cache tied to the player's GUID and the specific enchantment ID.
* **Item-Aware Invalidation:** To handle gear swaps properly (such as moving from a lower-tier Rare item to a high-end Epic or Legendary item), the cache tracks the specific `itemGuid` currently equipped in that slot. If a player swaps their gear, the item GUID changes, instantly invalidating the stale cache entry and triggering an accurate, fresh calculation.
* **Timed Expiration:** Cached entries automatically expire after a configurable duration (`NPCEnchanterEnhanced.DynamicPriceCacheDuration`), ensuring long-term memory doesn't bloat while keeping short-term interactions completely stable.
* **Manual Purging Commands:** Game masters can clear player price caches on-demand using the chat command system:
    * `.NPCEE clearcache` (Clears cache for the current player)
    * `.NPCEE clearcache [playername]` (Clears cache for a specific online player)
    * `.NPCEE clearallcache` (Wipes the pricing cache entirely across the board)

---

## How the Formula Works

The pricing engine uses a multiplicative model to capture exponential stat growth across expansions:

$$\text{Adjusted Price} = \text{Base Price} \times (1 + \text{Item Level} \times \text{iLvl Mult}) \times (1 + \text{Player Level} \times \text{pLvl Mult}) \times \text{Quality Multiplier}$$

* **Random Variance**: A final organic fluctuation of $\pm 15\%$ is applied so that prices shift slightly with each interaction.

---

## Online Testing Playground

If you want to tweak multipliers and test pricing outcomes **without having to restart your server or reload configs repeatedly**, you can use our pre-configured sandbox:

**[Click here to test formulas in the C++ Online Compiler](https://onecompiler.com/cpp/453zuggvp)**

---

## Expected Output & Price Brackets

The default configuration is heavily tuned against real retail expansion gear curves to hit specific economic targets for high-end epics:
* **Vanilla High-End (~150g–200g)**
* **TBC High-End (~350g–450g)**
* **WotLK High-End (~550g–700g)**

Running the test matrix produces the following sample costs:

```text
=== NPC Enchanter Enhanced: Comprehensive Price Matrix ===

[Vanilla] Leveling Green (iLvl 20, Lvl 25, Uncommon): 4 gold
[Vanilla] Pre-Raid Blue (iLvl 55, Lvl 60, Rare): 62 gold
[Vanilla] MC/BWL Raid Epic (iLvl 65, Lvl 60, Epic): 155 gold

[TBC] Leveling Green (iLvl 85, Lvl 65, Uncommon): 25 gold
[TBC] Heroic Dungeon Blue (iLvl 115, Lvl 70, Rare): 124 gold
[TBC] Sunwell/BT Raid Epic (iLvl 154, Lvl 70, Epic): 403 gold

[WotLK] Leveling Green (iLvl 140, Lvl 75, Uncommon): 40 gold
[WotLK] Naxx 25 Raid Epic (iLvl 213, Lvl 80, Epic): 643 gold
[WotLK] ICC 25 Heroic Epic (iLvl 277, Lvl 80, Epic): 770 gold
[WotLK] Legendary Weapon (iLvl 284, Lvl 80, Legendary): 1061 gold
```


### Want to experiment with the code?
If you'd like to inspect, modify, or run the pricing algorithm locally, you can expand the block below to view the complete standalone C++ script. It includes simulated configuration variables, quality enums, and the full test suite so you can easily run it in any local compiler or playground.

<details>
<summary>Standalone</summary>

```
#include <iostream>
#include <cstdint>
#include <random>

using uint32 = uint32_t;

enum ItemQuality {
ITEM_QUALITY_POOR      = 0,
ITEM_QUALITY_NORMAL    = 1,
ITEM_QUALITY_UNCOMMON  = 2,
ITEM_QUALITY_RARE      = 3,
ITEM_QUALITY_EPIC      = 4,
ITEM_QUALITY_LEGENDARY = 5,
ITEM_QUALITY_ARTIFACT  = 6,
ITEM_QUALITY_HEIRLOOM  = 7
};

enum class EnchantTier {
Leveling,
PreRaid,
Raid
};

// Simulated configuration variables (Normally loaded from .conf file)
uint32 NPCEnchanterEnhancedBasePriceLeveling = 2;
uint32 NPCEnchanterEnhancedBasePricePreRaid = 5;
uint32 NPCEnchanterEnhancedBasePriceRaid = 10;

float NPCEnchanterEnhancedItemLevelMultiplier = 0.05f;    // Tuned for multiplicative scaling
float NPCEnchanterEnhancedPlayerLevelMultiplier = 0.05f;  // Tuned for multiplicative scaling
float NPCEnchanterEnhancedQualityMultiplierNormal = 0.3f;
float NPCEnchanterEnhancedQualityMultiplierUncommon = 0.5f;
float NPCEnchanterEnhancedQualityMultiplierRare = 0.8f;
float NPCEnchanterEnhancedQualityMultiplierEpic = 1.0f;
float NPCEnchanterEnhancedQualityMultiplierLegendary = 1.35f;
float NPCEnchanterEnhancedVariancePercentage = 0.15f;

// Random variance helper
float frand(float min, float max) {
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(min, max);
return dis(gen);
}

// Standalone test function mimicking PriceHelper::CalculateDynamicEnchantPrice
uint32 CalculateTestPrice(EnchantTier tier, uint32 itemLevel, uint32 itemQuality, uint32 playerLevel)
{
uint32 basePrice = NPCEnchanterEnhancedBasePriceLeveling;
float qualityMultiplier = NPCEnchanterEnhancedQualityMultiplierNormal;
float variancePercentage = NPCEnchanterEnhancedVariancePercentage;

    // Tier base costs
    switch (tier)
    {
        case EnchantTier::Leveling: basePrice = NPCEnchanterEnhancedBasePriceLeveling; break;
        case EnchantTier::PreRaid:  basePrice = NPCEnchanterEnhancedBasePricePreRaid; break;
        case EnchantTier::Raid:     basePrice = NPCEnchanterEnhancedBasePriceRaid; break;
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

    float itemLevelAdjustment = static_cast<float>(itemLevel) * NPCEnchanterEnhancedItemLevelMultiplier;
    float playerLevelAdjustment = static_cast<float>(playerLevel) * NPCEnchanterEnhancedPlayerLevelMultiplier;

    // Multiplicative Formula across expansions
    float adjustedPrice = static_cast<float>(basePrice)
                        * (1.0f + itemLevelAdjustment)
                        * (1.0f + playerLevelAdjustment)
                        * qualityMultiplier;

    // Variance multiplier
    if (variancePercentage > 0.0f)
    {
        float minMultiplier = 1.0f - variancePercentage;
        float maxMultiplier = 1.0f + variancePercentage;
        adjustedPrice *= frand(minMultiplier, maxMultiplier);
    }

    return static_cast<uint32>(adjustedPrice);
}

int main()
{
std::cout << "=== NPC Enchanter Enhanced: Comprehensive Price Matrix ===\n\n";

    // --- VANILLA SCENARIOS ---
    std::cout << "[Vanilla] Leveling Green (iLvl 20, Lvl 25, Uncommon):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::Leveling, 20, ITEM_QUALITY_UNCOMMON, 25) << " gold\n\n";

    std::cout << "[Vanilla] Pre-Raid Blue (iLvl 55, Lvl 60, Rare):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::PreRaid, 55, ITEM_QUALITY_RARE, 60) << " gold\n\n";

    std::cout << "[Vanilla] MC/BWL Raid Epic (iLvl 65, Lvl 60, Epic):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::Raid, 65, ITEM_QUALITY_EPIC, 60) << " gold\n\n";

    // --- TBC SCENARIOS ---
    std::cout << "[TBC] Leveling Green (iLvl 85, Lvl 65, Uncommon):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::Leveling, 85, ITEM_QUALITY_UNCOMMON, 65) << " gold\n\n";

    std::cout << "[TBC] Heroic Dungeon Blue (iLvl 115, Lvl 70, Rare):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::PreRaid, 115, ITEM_QUALITY_RARE, 70) << " gold\n\n";

    std::cout << "[TBC] Sunwell/BT Raid Epic (iLvl 154, Lvl 70, Epic):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::Raid, 154, ITEM_QUALITY_EPIC, 70) << " gold\n\n";

    // --- WOTLK SCENARIOS ---
    std::cout << "[WotLK] Leveling Green (iLvl 140, Lvl 75, Uncommon):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::Leveling, 140, ITEM_QUALITY_UNCOMMON, 75) << " gold\n\n";

    std::cout << "[WotLK] Naxx 25 Raid Epic (iLvl 213, Lvl 80, Epic):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::Raid, 213, ITEM_QUALITY_EPIC, 80) << " gold\n\n";

    std::cout << "[WotLK] ICC 25 Heroic Epic (iLvl 277, Lvl 80, Epic):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::Raid, 277, ITEM_QUALITY_EPIC, 80) << " gold\n\n";

    std::cout << "[WotLK] Legendary Weapon (iLvl 284, Lvl 80, Legendary):\n  -> Price: "
              << CalculateTestPrice(EnchantTier::Raid, 284, ITEM_QUALITY_LEGENDARY, 80) << " gold\n";

    return 0;
}
```

</details>
