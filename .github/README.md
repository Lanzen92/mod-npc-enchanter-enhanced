# NPC Enchanter Enhanced 🧙‍♂️✨

[![License: AGPL v3](https://img.shields.io/badge/License--AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)
[![Platform: AzerothCore](https://img.shields.io/badge/AzerothCore-C++20-blue.svg)](https://www.azerothcore.org/)
[![Module Status: Active](https://img.shields.io/badge/Status-Active-success.svg)]()
[![Build Status](https://github.com/Lanzen92/mod_npc_enchanter_enchanced/actions/workflows/core-build.yml/badge.svg)](https://github.com/Lanzen92/mod_npc_enchanter_enchanced/actions/workflows/core-build.yml)
[![CodeStyle Status](https://github.com/Lanzen92/mod_npc_enchanter_enchanced/actions/workflows/core_codestyle.yml/badge.svg)](https://github.com/Lanzen92/mod_npc_enchanter_enchanced/actions/workflows/core_codestyle.yml)


**NPC Enchanter Enhanced** is an AzerothCore module inspired by the classic [`npc_enchanter module`](https://www.azerothcore.org/catalogue.html#/details/123951640).
I built this module completely for myself because I wanted something that actually matches my progression while playing solo, rather than relying on custom workarounds.
The goal is to keep it feeling genuinely Blizzlike while giving your solo character a natural way to stay enchanted as you level up.

Plus, I added a bunch of configurations so you can completely tailor it to whatever style you want, whether you want it strict or relaxed.

> **⚠️ Note / Disclaimer:** This is one of my first C++ project and my first custom module! You might run into bugs - Please feel free to open an issue or pull request if find any bugs or problems. - And always back up your database before installing new modules on a live server!

---

## 🚀 Key Features

* **Advanced Menu System:** Filter, disable, or hide unavailable enchants dynamically.
* **Summon Utility:** Conveniently summon a temporary enchanter on demand using `.NPCEE Spawn` (which can be configured to work for any player).
* **Flexible Restriction Modes:** Toggle between showing all enchants or using more "blizzlike" restrictions based on class, level, item level, professions, reputations, and phases.
* **Individual Progression:** Optional feature that looks at achievements/quests to unlock phase-specific enchants (fully standalone; `IndividualProgression` is not required). Phase tiers and logic provided by [Individual Progression](https://github.com/ZhengPeiRu21/mod-individual-progression). For a complete breakdown of supported tiers and phases, check out the [List of Progression Tiers Wiki](https://github.com/ZhengPeiRu21/mod-individual-progression/wiki/List-of-Progression-Tiers).
* **Comprehensive Spell Data:** Includes all enchants for Vanilla, TBC and WotLK. See all included enchants [here](https://docs.google.com/spreadsheets/d/1my52-abZ6ggKZbqpEuLy2mrlCYTh6S3YSQViI45kKKk/edit?usp=sharing). (Cost in the spreadsheets are only used if Dynamic Pricing and FreeEnchants are both disabled.)
* **Dynamic Pricing** - Designed to feel more "blizzlike," but fully customizable through a bunch of flexible configurations so you can tailor it to your exact preferences. [Read the Dynamic Pricing Guide](docs/DynamicPricing.md)

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
#
# Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
#

[worldserver]

#################################################################################################
#
# NPC Enchanter Enhanced
#
#################################################################################################

# -----------------------------------------------------------------------------------------------
#  General Settings
# -----------------------------------------------------------------------------------------------
#
#  NPCEnchanterEnhanced.Enabled
#    Enable the module.
#    Default: 1 (Enabled)
#           : 0 (Disabled)
#
NPCEnchanterEnhanced.Enabled = 1

#
#  NPCEnchanterEnhanced.Announce
#    Announce the module in chat when a player logs in.
#    Default: 1 (Enabled)
#           : 0 (Disabled)
#
NPCEnchanterEnhanced.Announce = 1


# -----------------------------------------------------------------------------------------------
#  NPC Behavior
# -----------------------------------------------------------------------------------------------
#
#  NPCEnchanterEnhanced.SpawnableByAnyone
#    Allow regular players to use the summon command (.NPCEE spawn).
#    Default: 1 (Any player)
#           : 0 (GMs / Admins only)
#
NPCEnchanterEnhanced.SpawnableByAnyone = 1

#
#  NPCEnchanterEnhanced.DespawnTimerInSeconds
#    Time in seconds before the summoned NPC automatically despawns.
#    Default: 90
#           : 0 (Never despawn)
#
NPCEnchanterEnhanced.DespawnTimerInSeconds = 90


# -----------------------------------------------------------------------------------------------
#  Filtering Requirements
# -----------------------------------------------------------------------------------------------
#  Bypass specific restrictions for enchants.
#  Default: 0 (Enforce restrictions)
#         : 1 (Ignore restrictions)
#
NPCEnchanterEnhanced.IgnoreProfessionRequirements   = 0
NPCEnchanterEnhanced.IgnoreLevelRequirements      = 0
NPCEnchanterEnhanced.IgnoreItemLevelRequirements  = 0
NPCEnchanterEnhanced.IgnoreClassRequirements      = 0
NPCEnchanterEnhanced.IgnoreReputationRequirements = 0

#
#  NPCEnchanterEnhanced.TiersToShow
#    Progression tiers displayed in the menu.
#    Options: Leveling, PreRaid, Raid
#    Default: "Leveling, PreRaid, Raid"
#
NPCEnchanterEnhanced.TiersToShow = "Leveling, PreRaid, Raid"

#
#  NPCEnchanterEnhanced.HideUnavailableEnchants
#    How to handle unowned or phase-locked enchants in the menu.
#    Default: 0 (Show as locked)
#           : 1 (Hide completely)
#
NPCEnchanterEnhanced.HideUnavailableEnchants = 0

#
#  NPCEnchanterEnhanced.OnlyShowCurrentOrLowerExpansionEnchants
#    Hide enchants from expansions higher than the current phase.
#    Default: 1 (Enabled)
#           : 0 (Disabled)
#
NPCEnchanterEnhanced.OnlyShowCurrentOrLowerExpansionEnchants = 1

# -----------------------------------------------------------------------------------------------
#  Phases & Progression
# -----------------------------------------------------------------------------------------------
#  Phase layout: 1-6 (Vanilla), 7-12 (TBC), 13-17 (WotLK)
#
#  NPCEnchanterEnhanced.Phase
#    Global phase cap. Enchants above this phase will be locked.
#    Default: 0 (Disabled)
#
NPCEnchanterEnhanced.Phase = 0

#
#  NPCEnchanterEnhanced.IndividualProgression
#    Tie phase locks to the player's IndividualProgression module achievements.
#    Note: This overrides NPCEnchanterEnhanced.Phase.
#    Default: 1 (Enabled)
#           : 0 (Disabled)
#
NPCEnchanterEnhanced.IndividualProgression = 1

# -----------------------------------------------------------------------------------------------
#  Pricing & Economy
# -----------------------------------------------------------------------------------------------
#
#  NPCEnchanterEnhanced.FreeEnchants
#    Make all enchants completely free of charge.
#    Default: 0 (Cost gold)
#           : 1 (Free)
#
NPCEnchanterEnhanced.FreeEnchants = 0

#
#  NPCEnchanterEnhanced.DynamicPricesOnEnchants
#    Enable dynamic economic price scaling based on item level, player level, and quality.
#    Note: Overrides FreeEnchants.
#    Default: 1 (Enabled)
#           : 0 (Disabled)
#
NPCEnchanterEnhanced.DynamicPricesOnEnchants = 1

#
#  Dynamic Price Calculation Formula:
#    1. Base Price        : Determined by the enchant's tier (Leveling, Pre-Raid, or Raid).
#    2. Item Level Adj    : 1.0 + (itemLevel * ItemLevelMultiplier)
#    3. Player Level Adj  : 1.0 + (playerLevel * PlayerLevelMultiplier)
#    4. Quality Multiplier: Scales the subtotal based on item quality (Normal, Epic, Legendary, etc.).
#    5. Final Calculation : Base Price * Item Level Adj * Player Level Adj * Quality Multiplier
#    6. Random Variance   : A random percentage fluctuation applied to the final cost (+/- Configured %).
#
DynamicPriceCacheDurationInSeconds = 1800

# Base Prices per Tier
NPCEnchanterEnhanced.BasePriceLeveling = 2
NPCEnchanterEnhanced.BasePricePreRaid  = 5
NPCEnchanterEnhanced.BasePriceRaid     = 10

# Scaling Multipliers & Variance
NPCEnchanterEnhanced.ItemLevelMultiplier       = 0.05
NPCEnchanterEnhanced.PlayerLevelMultiplier     = 0.05
NPCEnchanterEnhanced.QualityMultiplierNormal   = 0.3
NPCEnchanterEnhanced.QualityMultiplierUncommon = 0.5
NPCEnchanterEnhanced.QualityMultiplierRare     = 0.8
NPCEnchanterEnhanced.QualityMultiplierEpic     = 1.0
NPCEnchanterEnhanced.QualityMultiplierLegendary= 1.35
NPCEnchanterEnhanced.VariancePercentage        = 0.15

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

