/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

// From SC
void AddSC_NPCEnchanterEnhanced();
void AddSC_NPCEnchanterEnhancedConfigManager();
void AddSC_NPCEnchanterEnhancedChatCommands();

// Add all
// cf. the naming convention https://github.com/azerothcore/azerothcore-wotlk/blob/master/doc/changelog/master.md#how-to-upgrade-4
// additionally replace all '-' in the module folder name with '_' here
void Addmod_npc_enchanter_enchancedScripts()
{
    AddSC_NPCEnchanterEnhanced();
    AddSC_NPCEnchanterEnhancedConfigManager();
    AddSC_NPCEnchanterEnhancedChatCommands();
}

