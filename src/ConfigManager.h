#pragma once

#include "Define.h"
#include "Config.h"

//Global values
extern const uint32 NPCEnchanterID;

//Confvalues
extern bool NPCEnchanterEnhancedEnabled;
extern bool NPCEnchanterEnhancedAnnounce;

//Filtering
extern bool NPCEnchanterEnhancedIgnoreProfessionRequirements;
extern bool NPCEnchanterEnhancedIgnoreLevelRequirements;
extern bool NPCEnchanterEnhancedIgnoreItemLevelRequirements;
extern bool NPCEnchanterEnhancedIgnoreClassRequirements;
extern std::string NPCEnchanterEnhancedTiersToShow;
extern bool NPCEnchanterEnhancedHideUnavailableEnchants;

//NPC
extern bool NPCEnchanterEnhancedSpawnableByAnyone;
extern uint32 NPCEnchanterEnhancedDespawnTimerInSeconds;

//Phases
extern uint32 NPCEnchanterEnhancedPhase;
extern bool NPCEnchanterEnhancedIndividualProgression;

//Prices
extern bool NPCEnchanterEnhancedFreeEnchants;
extern bool NPCEnchanterEnhancedDynamicPricesOnEnchants;

void LoadEnchantConfig(bool reload = false);

