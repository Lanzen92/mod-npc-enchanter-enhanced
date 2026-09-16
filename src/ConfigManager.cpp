#include "ConfigManager.h"
#include "Define.h"
#include "Config.h"
#include "ScriptMgr.h"

//Global
extern const uint32 NPCEnchanterID = 602050;

//Confvalues
bool NPCEnchanterEnhancedEnabled = false;
bool NPCEnchanterEnhancedAnnounce= false;

//Filtering
bool NPCEnchanterEnhancedIgnoreProfessionRequirements = false;
bool NPCEnchanterEnhancedIgnoreLevelRequirements = false;
bool NPCEnchanterEnhancedIgnoreItemLevelRequirements = false;
bool NPCEnchanterEnhancedIgnoreClassRequirements = false;
bool NPCEnchanterEnhancedHideUnavailableEnchants = false;

//NPC
bool NPCEnchanterEnhancedSpawnableByAnyone = false;
uint32 NPCEnchanterEnhancedDespawnTimerInSeconds = 90;

//Phases
bool NPCEnchanterEnhancedIndividualProgression = false;
uint32 NPCEnchanterEnhancedPhase = 1;

//Prices
bool NPCEnchanterEnhancedFreeEnchants = false;
bool NPCEnchanterEnhancedDynamicPricesOnEnchants = false;

//Dynamic Pricing Parameters
uint32 NPCEnchanterEnhancedBasePriceLeveling = 10;
uint32 NPCEnchanterEnhancedBasePricePreRaid = 50;
uint32 NPCEnchanterEnhancedBasePriceRaid = 200;

//Dynamic Pricing Multipliers
float NPCEnchanterEnhancedItemLevelMultiplier = 0.1f;
float NPCEnchanterEnhancedPlayerLevelMultiplier = 0.2f;
float NPCEnchanterEnhancedQualityMultiplierNormal = 0.5f;
float NPCEnchanterEnhancedQualityMultiplierUncommon = 0.8f;
float NPCEnchanterEnhancedQualityMultiplierRare = 1.0f;
float NPCEnchanterEnhancedQualityMultiplierEpic = 1.25f;
float NPCEnchanterEnhancedQualityMultiplierLegendary = 1.75f;

float NPCEnchanterEnhancedVariancePercentage = 0.15f;

void LoadEnchantConfig(bool /*reload*/)
{
    NPCEnchanterEnhancedEnabled = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.Enabled", true);
    NPCEnchanterEnhancedAnnounce = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.Announce", true);

    NPCEnchanterEnhancedIgnoreProfessionRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreProfessionRequirements", false);
    NPCEnchanterEnhancedIgnoreLevelRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreLevelRequirements", false);
    NPCEnchanterEnhancedIgnoreItemLevelRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreItemLevelRequirements", false);
    NPCEnchanterEnhancedIgnoreClassRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreClassRequirements", false);
    NPCEnchanterEnhancedHideUnavailableEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.HideUnavailableEnchants", false);

    //Load this on the fly in the ValidationHelper instead.. (bugprone-throwing-static-initialization)
    //NPCEnchanterEnhancedTiersToShow = sConfigMgr->GetOption<std::string>("NPCEnchanterEnhanced.TiersToShow", "Leveling, PreRaid, Raid");

    NPCEnchanterEnhancedSpawnableByAnyone = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.SpawnableByAnyone", true);
    NPCEnchanterEnhancedDespawnTimerInSeconds = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.DespawnTimerInSeconds", 120);

    NPCEnchanterEnhancedIndividualProgression = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IndividualProgression", false);
    NPCEnchanterEnhancedPhase = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.Phase", 1);

    NPCEnchanterEnhancedFreeEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.FreeEnchants", false);

    NPCEnchanterEnhancedDynamicPricesOnEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.DynamicPricesOnEnchants", false);
    NPCEnchanterEnhancedBasePriceLeveling = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.BasePriceLeveling", 10);
    NPCEnchanterEnhancedBasePricePreRaid = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.BasePricePreRaid", 50);
    NPCEnchanterEnhancedBasePriceRaid = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.BasePriceRaid", 200);

    NPCEnchanterEnhancedItemLevelMultiplier = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.ItemLevelMultiplier", 0.1f);
    NPCEnchanterEnhancedPlayerLevelMultiplier = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.PlayerLevelMultiplier", 0.2f);
    NPCEnchanterEnhancedQualityMultiplierNormal = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierNormal", 0.5f);
    NPCEnchanterEnhancedQualityMultiplierUncommon = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierUncommon", 0.8f);
    NPCEnchanterEnhancedQualityMultiplierRare = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierRare", 1.0f);
    NPCEnchanterEnhancedQualityMultiplierEpic = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierEpic", 1.25f);
    NPCEnchanterEnhancedQualityMultiplierLegendary = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.QualityMultiplierLegendary", 1.75f);

    NPCEnchanterEnhancedVariancePercentage = sConfigMgr->GetOption<float>("NPCEnchanterEnhanced.VariancePercentage", 0.15f);

    if (NPCEnchanterEnhancedDynamicPricesOnEnchants)
    {
        NPCEnchanterEnhancedFreeEnchants = false;
    }
};

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

void AddSC_NPCEnchanterEnhancedConfigManager()
{
    new NPCEnchanterEnhancedConfigManager();
}
