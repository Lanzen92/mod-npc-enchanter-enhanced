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
extern bool NPCEnchanterEnhancedOnlyAllowSameOrLowerExpansion;

//Prices
extern bool NPCEnchanterEnhancedFreeEnchants;

//Dynamic prices
extern bool NPCEnchanterEnhancedDynamicPricesOnEnchants;
extern uint32 NPCEnchanterEnhancedBasePriceLeveling;
extern uint32 NPCEnchanterEnhancedBasePricePreRaid;
extern uint32 NPCEnchanterEnhancedBasePriceRaid;
//
extern float NPCEnchanterEnhancedItemLevelMultiplier;
extern float NPCEnchanterEnhancedPlayerLevelMultiplier;
//
extern float NPCEnchanterEnhancedQualityMultiplierNormal;
extern float NPCEnchanterEnhancedQualityMultiplierUncommon;
extern float NPCEnchanterEnhancedQualityMultiplierRare;
extern float NPCEnchanterEnhancedQualityMultiplierEpic;
extern float NPCEnchanterEnhancedQualityMultiplierLegendary;

extern float NPCEnchanterEnhancedVariancePercentage;
extern float NPCEnchanterEnhancedDynamicPriceCacheDurationInSeconds;

void LoadEnchantConfig(bool reload = false);
