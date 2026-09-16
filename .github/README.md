# NPC Enchanter Enhanced 🧙‍♂️✨

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: AzerothCore](https://img.shields.io/badge/AzerothCore-C++17-blue.svg)](https://www.azerothcore.org/)
[![Module Status: Active](https://img.shields.io/badge/Status-Active-success.svg)]()


**NPC Enchanter Enhanced** is an AzerothCore module inspired by the classic [`npc_enchanter module`](https://www.azerothcore.org/catalogue.html#/details/123951640). It makes in-game enchanting easy and flexible by letting players apply enchants directly through a clean NPC menu, using custom costs, items, and rules for a better quality-of-life experience.

> **⚠️ Note / Disclaimer:** This is my first-ever C++ project and my first custom module! While I've tested it thoroughly, you might run into minor edge cases or quirks. Please feel free to open an issue or pull request if you spot anything, and always back up your database before installing new modules on a live server!

---

## 🚀 Key Features

* **Advanced Menu System:** Filter, disable, or hide unavailable enchants dynamically.
* **Summon Utility:** Conveniently summon a temporary enchanter on demand using `.NPCEE Spawn` (which can be configured to work for any player).
* **Flexible Restriction Modes:** Toggle between showing all enchants or using more "blizzlike" restrictions based on class, level, item level, professions, and phases.
* **Progression Integration:** Optional integration with `IndividualProgression` to check player achievements and automatically unlock enchants released for that specific phase (fully implemented as a standalone feature, so `IndividualProgression` is not required).
* **Comprehensive Spell Data:** Includes all Vanilla enchants right out of the box, with TBC and WotLK enchants planned for upcoming updates.

Upcoming features/changes:
* **More enchants** - Of course, all of the TBC and WotLK enchants!
* **Dynamic Pricing** - To make it feel more "blizzlike". 
* **Items** - A book that players can buy and use to summon Enchanter Xari.
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
* [AzerothCore Community](https://www.azerothcore.org/) for the incredible open-source framework.
* All contributors and testers who helped shape this project.
* Also big thanks to [StygianTheBest](https://github.com/StygianTheBest) and [gtao725](https://github.com/gtao725/) for the inspiration! 

