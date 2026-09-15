#pragma once

#include "Define.h"

//Global values
extern const uint32 NPCEnchanterID;

extern bool NPCEnchanterEnhancedEnabled;
extern bool NPCEnchanterEnhancedAnnounce;

//Filter
extern bool NPCEnchanterEnhancedIgnoreProfessionRequirements;
extern bool NPCEnchanterEnhancedIgnoreLevelRequirements;
extern bool NPCEnchanterEnhancedIgnoreItemLevelRequirements;
extern bool NPCEnchanterEnhancedIgnoreClassRequirements;
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

