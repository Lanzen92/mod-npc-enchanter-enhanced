/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 * Copyright (C) 2026 Lanzen92 https://github.com/Lanzen92/mod_npc_enchanter_enchanced
 * This file is part of mod_npc_enchanter_enchanced.
 */

#include "ConfigManager.h"
#include "Define.h"
#include "Config.h"
#include "ScriptMgr.h"

//Global
extern const uint32 NPCEnchanterID = 602050;

//Confvalues
bool NPCEnchanterEnhancedEnabled = true;
bool NPCEnchanterEnhancedAnnounce = true;

//NPC
bool NPCEnchanterEnhancedSpawnableByAnyone = true;
uint32 NPCEnchanterEnhancedDespawnTimerInSeconds = 90;

//Filtering
bool NPCEnchanterEnhancedIgnoreProfessionRequirements = false;
bool NPCEnchanterEnhancedIgnoreLevelRequirements = false;
bool NPCEnchanterEnhancedIgnoreItemLevelRequirements = false;
bool NPCEnchanterEnhancedIgnoreClassRequirements = false;
bool NPCEnchanterEnhancedIgnoreReputationRequirements = false;
bool NPCEnchanterEnhancedHideUnavailableEnchants = false;

//Phases
bool NPCEnchanterEnhancedIndividualProgression = true;
uint32 NPCEnchanterEnhancedPhase = 0;
bool NPCEnchanterEnhancedOnlyShowCurrentExpansionEnchants = true;

//Prices
bool NPCEnchanterEnhancedFreeEnchants = false;
bool NPCEnchanterEnhancedDynamicPricesOnEnchants = false;

//Dynamic Pricing Parameters
float NPCEnchanterEnhancedDynamicPriceCacheDurationInSeconds = 1800;
uint32 NPCEnchanterEnhancedBasePriceLeveling = 10;
uint32 NPCEnchanterEnhancedBasePricePreRaid = 50;
uint32 NPCEnchanterEnhancedBasePriceRaid = 200;

//Dynamic Pricing Multipliers
float NPCEnchanterEnhancedItemLevelMultiplier = 0.1f;
float NPCEnchanterEnhancedPlayerLevelMultiplier = 0.2f;
float NPCEnchanterEnhancedQualityMultiplierNormal = 0.3f;
float NPCEnchanterEnhancedQualityMultiplierUncommon = 0.5f;
float NPCEnchanterEnhancedQualityMultiplierRare = 0.8f;
float NPCEnchanterEnhancedQualityMultiplierEpic = 1.0f;
float NPCEnchanterEnhancedQualityMultiplierLegendary = 1.35f;
float NPCEnchanterEnhancedVariancePercentage = 0.15f;

void LoadEnchantConfig(bool /*reload*/)
{
    NPCEnchanterEnhancedEnabled = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.Enabled", true);
    NPCEnchanterEnhancedAnnounce = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.Announce", true);

    NPCEnchanterEnhancedSpawnableByAnyone = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.SpawnableByAnyone", true);
    NPCEnchanterEnhancedDespawnTimerInSeconds = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.DespawnTimerInSeconds", 90);

    NPCEnchanterEnhancedIgnoreProfessionRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreProfessionRequirements", false);
    NPCEnchanterEnhancedIgnoreLevelRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreLevelRequirements", false);
    NPCEnchanterEnhancedIgnoreItemLevelRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreItemLevelRequirements", false);
    NPCEnchanterEnhancedIgnoreClassRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreClassRequirements", false);
    NPCEnchanterEnhancedIgnoreReputationRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreReputationRequirements", false);
    NPCEnchanterEnhancedHideUnavailableEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.HideUnavailableEnchants", false);

    //Load this on the fly in the ValidationHelper instead.. (bugprone-throwing-static-initialization)
    //NPCEnchanterEnhancedTiersToShow = sConfigMgr->GetOption<std::string>("NPCEnchanterEnhanced.TiersToShow", "Leveling, PreRaid, Raid");

    NPCEnchanterEnhancedIndividualProgression = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IndividualProgression", true);
    NPCEnchanterEnhancedPhase = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.Phase", 0);
    NPCEnchanterEnhancedOnlyShowCurrentExpansionEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.OnlyAllowPhaseExpansion", true);

    NPCEnchanterEnhancedFreeEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.FreeEnchants", false);
    NPCEnchanterEnhancedDynamicPricesOnEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.DynamicPricesOnEnchants", false);

    NPCEnchanterEnhancedDynamicPriceCacheDurationInSeconds =sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.DynamicPriceCacheDurationInSeconds", 1800);
    NPCEnchanterEnhancedBasePriceLeveling = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.BasePriceLeveling", 10);
    NPCEnchanterEnhancedBasePricePreRaid = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.BasePricePreRaid", 50);
    NPCEnchanterEnhancedBasePriceRaid = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.BasePriceRaid", 200);

    NPCEnchanterEnhancedItemLevelMultiplier = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.ItemLevelMultiplier", 0.1f);
    NPCEnchanterEnhancedPlayerLevelMultiplier = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.PlayerLevelMultiplier", 0.2f);
    NPCEnchanterEnhancedQualityMultiplierNormal = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierNormal", 0.3f);
    NPCEnchanterEnhancedQualityMultiplierUncommon = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierUncommon", 0.5f);
    NPCEnchanterEnhancedQualityMultiplierRare = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierRare", 0.8f);
    NPCEnchanterEnhancedQualityMultiplierEpic = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierEpic", 1.0f);
    NPCEnchanterEnhancedQualityMultiplierLegendary = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierLegendary", 1.35f);
    NPCEnchanterEnhancedVariancePercentage = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.VariancePercentage", 0.15f);

    if (NPCEnchanterEnhancedDynamicPricesOnEnchants)
    {
        NPCEnchanterEnhancedFreeEnchants = false;
    }
};

namespace
{
    // Hook configuration loading into server startup and reloads
    class NPCEnchanterEnhancedConfigManager : public WorldScript
    {
    public:
        NPCEnchanterEnhancedConfigManager() : WorldScript("NPCEnchanterEnhancedConfigManager") {}

        void OnStartup() override
        {
            LoadEnchantConfig(false);
        }

        void OnConfigLoad(bool reload)
        {
            LoadEnchantConfig(reload);
        }
    };
}

void AddSC_NPCEnchanterEnhancedConfigManager()
{
    new NPCEnchanterEnhancedConfigManager();
}
