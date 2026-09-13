#pragma once

#include "Define.h"

//Global values
extern const uint32 NPCEnchanter_ID;

//Confvalues
extern bool NPCEnchanterEnhancedEnabled;
extern bool NPCEnchanterEnhancedAnnounce;
extern bool NPCEnchanterEnhancedSpawnableByAnyone;
extern uint32 NPCEnchanterEnhancedDespawnTimerInSeconds;
extern bool NPCEnchanterEnhancedLockProfessionEnchants;
//Phases
extern uint32 NPCEnchanterEnhancedPhase;
extern bool NPCEnchanterEnhancedIndividualProgression;
//Prices
extern bool NPCEnchanterEnhancedFreeEnchants;
extern bool NPCEnchanterEnhancedDynamicPricesOnEnchants;

void LoadEnchantConfig(bool reload = false);

