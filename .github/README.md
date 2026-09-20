# NPC Enchanter Enhanced 🧙‍♂️✨

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
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
* **Individual Progression:** Optional feature that looks at the same achievements/quests to unlock phase-specific enchants (fully standalone; `IndividualProgression` is not required).
* **Comprehensive Spell Data:** Includes all Vanilla enchants right out of the box, with TBC and WotLK enchants planned for upcoming updates.
* **Dynamic Pricing** - Designed to feel more "blizzlike," but fully customizable through a bunch of flexible configurations so you can tailor it to your exact needs.

## 📄 In the backlog:
* **More enchants** - Of course, all of the TBC and WotLK enchants!
* **Items** - A book that players can buy and use to summon Enchanter Xari.
* **Polish** - Alooot of testing and probably alot of bugfixing.
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

Coming later.. :)

---

## 🤝 Contributing

Contributions, bug reports, and feature requests are always welcome!

---

## 📜 License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

---

## 🙏 Acknowledgements

*  [AzerothCore Community](https://www.azerothcore.org/) for the incredible open-source framework.
* All contributors and testers who helped shape this project.
* The creators and contributors of [`mod-individual-progression`](https://www.azerothcore.org/catalogue.html#/details/467290212) and 
[`npc_enchanter module`](https://www.azerothcore.org/catalogue.html#/details/123951640).

