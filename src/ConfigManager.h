/*
* Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

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
extern bool NPCEnchanterEnhancedIgnoreReputationRequirements;
extern bool NPCEnchanterEnhancedHideUnavailableEnchants;

//NPC
extern bool NPCEnchanterEnhancedSpawnableByAnyone;
extern uint32 NPCEnchanterEnhancedDespawnTimerInSeconds;

//Phases
extern uint32 NPCEnchanterEnhancedPhase;
extern bool NPCEnchanterEnhancedIndividualProgression;
extern bool NPCEnchanterEnhancedOnlyAllowPhaseExpansion;

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
