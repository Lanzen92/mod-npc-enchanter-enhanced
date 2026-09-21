# NPC Enchanter Enhanced 🧙‍♂️✨

[![License: AGPL v3](https://img.shields.io/badge/License--AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)
[![Platform: AzerothCore](https://img.shields.io/badge/AzerothCore-C++17-blue.svg)](https://www.azerothcore.org/)
[![Module Status: Active](https://img.shields.io/badge/Status-Active-success.svg)]()
[![Build Status](https://github.com/Lanzen92/mod_npc_enchanter_enchanced/actions/workflows/core-build.yml/badge.svg)](https://github.com/Lanzen92/mod_npc_enchanter_enchanced/actions/workflows/core-build.yml)
[![CodeStyle Status](https://github.com/Lanzen92/mod_npc_enchanter_enchanced/actions/workflows/core_codestyle.yml/badge.svg)](https://github.com/Lanzen92/mod_npc_enchanter_enchanced/actions/workflows/core_codestyle.yml)


**NPC Enchanter Enhanced** is an AzerothCore module inspired by the classic [`npc_enchanter module`](https://www.azerothcore.org/catalogue.html#/details/123951640). 
I built this module completely for myself because I wanted something that actually matches my progression while playing solo, rather than relying on custom workarounds.
The goal is to keep it feeling genuinely Blizzlike while giving your solo character a natural way to stay enchanted as you level up.

Plus, I added a bunch of configurations so you can completely tailor it to whatever style you want, whether you want it strict or relaxed.

> **⚠️ Note / Disclaimer:** This is one of my first C++ project and my first custom module! You might run into bugs - Please feel free to open an issue or pull request if you spot anything, and always back up your database before installing new modules on a live server!

---

## 🚀 Key Features

* **Advanced Menu System:** Filter, disable, or hide unavailable enchants dynamically.
* **Summon Utility:** Conveniently summon a temporary enchanter on demand using `.NPCEE Spawn` (which can be configured to work for any player).
* **Flexible Restriction Modes:** Toggle between showing all enchants or using more "blizzlike" restrictions based on class, level, item level, professions, and phases.
* **Individual Progression:** Optional feature that looks at achievements/quests to unlock phase-specific enchants (fully standalone; `IndividualProgression` is not required). Phase tiers and logic provided by [Individual Progression](https://github.com/ZhengPeiRu21/mod-individual-progression). For a complete breakdown of supported tiers and phases, check out the [List of Progression Tiers Wiki](https://github.com/ZhengPeiRu21/mod-individual-progression/wiki/List-of-Progression-Tiers).
* **Comprehensive Spell Data:** Includes all enchants for Vanilla, TBC and WotLK. See all included enchants [here](https://docs.google.com/spreadsheets/d/1my52-abZ6ggKZbqpEuLy2mrlCYTh6S3YSQViI45kKKk/edit?usp=sharing). (Cost in the spreadsheets are only used if Dynamic Pricing and FreeEnchants are both disabled.)
* **Dynamic Pricing** - Designed to feel more "blizzlike," but fully customizable through a bunch of flexible configurations so you can tailor it to your exact preferences.

## 📄 In the backlog:
* **Items** - A book that players can buy and use to summon Enchanter Xari.
* **Testing and bugfixing** - Alot of testing and prob alot of bugfixing needed.
---

## 📦 Installation

1. **Navigate to your AzerothCore modules directory:**
   ```bash
   cd /path/to/azerothcore/modules 
   ```
2. **Clone or copy the module repository:**
   ```bash
   git clone [https://github.com/lanzen92/mod-npc-enchanter-enhanced.git](https://github.com/lanzen92/mod-npc-enchanter-enhanced.git)
   ```
3. **Clone or copy the module repository:**
   ```bash
   cd /path/to/azerothcore/build
   cmake ../ -DCMAKE_INSTALL_PREFIX=/path/to/azerothcore/server
   make -j$(nproc)
   make install
   ```
---

## ⚙️ Configuration
<details>
<summary>Configurations</summary>

Out of the box, the default settings are set up to give you that a somewhat authentic, original game feel. 

```
########################################
# NPC Enchanter Enhanced
########################################
# -------------------------------------------------------------------------------------
#  Enable the module
#
#  Enable : 1
#  Disable: 0
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.Enabled = 1

# -------------------------------------------------------------------------------------
#  Announce
#
#  Announce the module when the player logs in?
#  Enable : 1
#  Disable: 0
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.Announce = 1

# -------------------------------------------------------------------------------------
#
#  NPC Settings
#
# -------------------------------------------------------------------------------------
#  SpawnableByAnyone
#
#  If the NPC should be spawnable for anyone. (.NPCEE spawn)
#  Enable : 1 (Any player can summon the enchanter)
#  Disable: 0 (Only GM/Admin can summon the enchanter)
#  Default: 1
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.SpawnableByAnyone = 1
#
# -------------------------------------------------------------------------------------
#  DespawnTimerInSeconds
#
#  NPC DespawnTimer in seconds
#  0 = Dont despawn.
#  1+ = Despawn after x seconds.
#  Default: 90
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.DespawnTimerInSeconds = 90
#
#--------------------------------------------------------------------------------------

# -------------------------------------------------------------------------------------
#
#  Filtering - Ignore different requirements
#
# -------------------------------------------------------------------------------------
#  IgnoreRequirements
#
#  NPCEnchanterEnhanced.IgnoreProfessionRequirements: Ignore profession requirements. for example Rocket Boots (Engineering), ring enchants (Enchanting) etc
#  NPCEnchanterEnhanced.IgnoreLevelRequirements: Ignore level requirements.
#  NPCEnchanterEnhanced.IgnoreItemLevelRequirements: Ignore itemlevel requirements.
#  NPCEnchanterEnhanced.IgnoreClassRequirements: Ignore class requirements. (ZG enchants etc)
#  NPCEnchanterEnhanced.IgnoreReputationRequirements: Ignore reputation requirements.
#
#  Enable : 1 - Ignores requirements
#  Disable: 0
#
#  Defaults values:
#  NPCEnchanterEnhanced.IgnoreProfessionRequirements = 0
#  NPCEnchanterEnhanced.IgnoreLevelRequirements = 0
#  NPCEnchanterEnhanced.IgnoreItemLevelRequirements = 0
#  NPCEnchanterEnhanced.IgnoreClassRequirements = 0
#  NPCEnchanterEnhanced.IgnoreReputationRequirements = 0
#
NPCEnchanterEnhanced.IgnoreProfessionRequirements = 0
NPCEnchanterEnhanced.IgnoreLevelRequirements = 0
NPCEnchanterEnhanced.IgnoreItemLevelRequirements = 0
NPCEnchanterEnhanced.IgnoreClassRequirements = 0
NPCEnchanterEnhanced.IgnoreReputationRequirements = 0
#
# -------------------------------------------------------------------------------------
#  TiersToShow
#
#   Raid: Crusader, +15 Agility, 30+ Spell Power, 55+ Healing Power, +4 Stats etc
#   PreRaid: +3 Stats etc
#   Leveling: Low-level enchants like Striking, Impact, Lesser Spirit etc
#
#  Show all tiers: "Leveling, PreRaid, Raid"
#  Default: "Leveling, PreRaid, Raid"
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.TiersToShow = "Leveling, PreRaid, Raid"
#
# -------------------------------------------------------------------------------------
#  HideUnavailableEnchants
#
#  If enchants are unavailable (Reasons like wrong phase, wrong class, to low level etc)
#  Hide enchants : 1
#  Show enchants but locked : 1
#  Default: 0
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.HideUnavailableEnchants = 0
#
#--------------------------------------------------------------------------------------

# -------------------------------------------------------------------------------------
#
#  Phases
#  Lock enchants that was not available in the current phase.
#  1-6 Vanilla
#  7-12 TBC
#  13-17 WOTLK
#
# -------------------------------------------------------------------------------------
#  NPCEnchanterEnhancedPhase
#
#  Only enable enchants that were available during this phase (Or lower)
#  Enable : 1-17
#  Disable: 0
#  Default: 0
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.Phase = 0
#
# -------------------------------------------------------------------------------------
#  IndividualProgression - !! This will override NPCEnchanterEnhancedPhase !!
#
#  Only enable enchants that were available during the player's current IndividualProgression phase.
#  Uses the same achievements as the IndividualProgression-module for phases.
#  Enable : 1
#  Disable: 0
#  Default: 1
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.IndividualProgression = 1
#
# -------------------------------------------------------------------------------------
#  NPCEnchanterEnhancedOnlyAllowPhaseExpansion
#
#  Only enable enchants for the current expansion (Based on phase)
#  This will hide Vanilla / TBC enchants if WotLK Phase for example.
#
#  Enable : 1
#  Disable: 0
#  Default: 1
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.NPCEnchanterEnhancedOnlyAllowPhaseExpansion = 1

#--------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------
#
#  Prices
#
# -------------------------------------------------------------------------------------
#  FreeEnchants
#
#  Enable free enchants
#  Enable : 1 Enchants are free.
#  Disable: 0 Enchants cost gold.
#  Default: 0
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.FreeEnchants = 0
#
# -------------------------------------------------------------------------------------
#  DynamicPricesOnEnchants - !! This will override FreeEnchants !!
#
#  Enable dynamic prices on enchants (Requires populated AH.) Not implemented yet.
#  Enable : 1
#  Disable: 0
#  Default: 1
# -------------------------------------------------------------------------------------
NPCEnchanterEnhanced.DynamicPricesOnEnchants = 0
#
#  Dynamice Prices variables
#
#  BasePrices
#  Base cost of the enchants, based on tiers (Leveling, PreRaid, Raid)
#
#  Multipliers
#  To make the prices more configurable and dynamic.
#  These are based on Player level, Itemlevel of the item and Quality of the item.
#
#  VariancePercentage - Makes the price be +- X % (0.15 = 15%)
#
#  Enchant Price Calculation Formula:
#    1. Base Price: Determined by the enchant's progression tier (Leveling, Pre-Raid, or Raid).
#    2. Item Level Scaling: itemLevel * ItemLevelMultiplier
#    3. Player Level Scaling: playerLevel * PlayerLevelMultiplier
#    4. Quality Multiplier: Scales the subtotal based on the item's quality (Normal, Epic, Legendary, etc.).
#    5. Random Variance: A random percentage fluctuation applied to the cost
#       based on the configured variance percentage (e.g., +/- 10%).
#
#    Final Price = ((Base Price + Item Level Adjustment + Player Level Adjustment) * Quality Multiplier) * Random Variance
#
#  Default values:
#  DynamicPriceCacheDurationInSeconds = 1800 (30 minutes)
#  NPCEnchanterEnhanced.BasePriceLeveling = 10
#  NPCEnchanterEnhanced.BasePricePreRaid = 50
#  NPCEnchanterEnhanced.BasePriceRaid = 200
#  NPCEnchanterEnhanced.ItemLevelMultiplier = 0.1
#  NPCEnchanterEnhanced.PlayerLevelMultiplier = 0.2
#  NPCEnchanterEnhanced.QualityMultiplierNormal = 0.3
#  NPCEnchanterEnhanced.QualityMultiplierUncommon = 0.5
#  NPCEnchanterEnhanced.QualityMultiplierRare = 0.8
#  NPCEnchanterEnhanced.QualityMultiplierEpic = 1.0
#  NPCEnchanterEnhanced.QualityMultiplierLegendary = 1.35
#  NPCEnchanterEnhanced.VariancePercentage = 0.15
#
DynamicPriceCacheDurationInSeconds = 1800
#
NPCEnchanterEnhanced.BasePriceLeveling = 10
NPCEnchanterEnhanced.BasePricePreRaid = 50
NPCEnchanterEnhanced.BasePriceRaid = 200
#
#  Multipliers
#
NPCEnchanterEnhanced.ItemLevelMultiplier = 0.1
NPCEnchanterEnhanced.PlayerLevelMultiplier = 0.2
NPCEnchanterEnhanced.QualityMultiplierNormal = 0.3
NPCEnchanterEnhanced.QualityMultiplierUncommon = 0.5
NPCEnchanterEnhanced.QualityMultiplierRare = 0.8
NPCEnchanterEnhanced.QualityMultiplierEpic = 1.0
NPCEnchanterEnhanced.QualityMultiplierLegendary = 1.35
NPCEnchanterEnhanced.VariancePercentage = 0.15
#
#-------------------------------------------------------------------------------------
```
</details>

---

## 🤝 Contributing

Contributions, bug reports, and feature requests are always welcome!

---

## 📜 License

Distributed under the GNU AGPL v3 License. See [LICENSE](LICENSE) for more information.

---

## 🙏 Acknowledgements

*  [AzerothCore Community](https://www.azerothcore.org/) for the incredible open-source framework.
* All contributors and testers who helped shape this project.
* The creators and contributors of [`mod-individual-progression`](https://www.azerothcore.org/catalogue.html#/details/467290212) and 
[`npc_enchanter module`](https://www.azerothcore.org/catalogue.html#/details/123951640).

