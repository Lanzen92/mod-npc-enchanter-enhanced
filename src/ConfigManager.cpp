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

void LoadEnchantConfig(bool /*reload*/)
{
    NPCEnchanterEnhancedEnabled = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.Enabled", true);
    NPCEnchanterEnhancedAnnounce = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.Announce", true);

    NPCEnchanterEnhancedIgnoreProfessionRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreProfessionRequirements", false);
    NPCEnchanterEnhancedIgnoreLevelRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreLevelRequirements", false);
    NPCEnchanterEnhancedIgnoreItemLevelRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreItemLevelRequirements", false);
    NPCEnchanterEnhancedIgnoreClassRequirements = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IgnoreClassRequirements", false);
    NPCEnchanterEnhancedHideUnavailableEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.HideUnavailableEnchants", false);

    //Load this on the fly in the ValidationHelper. (bugprone-throwing-static-initialization)
    //NPCEnchanterEnhancedTiersToShow = sConfigMgr->GetOption<std::string>("NPCEnchanterEnhanced.TiersToShow", "Leveling, PreRaid, Raid");

    NPCEnchanterEnhancedSpawnableByAnyone = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.SpawnableByAnyone", true);
    NPCEnchanterEnhancedDespawnTimerInSeconds = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.DespawnTimerInSeconds", 120);

    NPCEnchanterEnhancedIndividualProgression = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IndividualProgression", false);
    NPCEnchanterEnhancedPhase = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.Phase", 1);

    NPCEnchanterEnhancedFreeEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.FreeEnchants", false);
    NPCEnchanterEnhancedDynamicPricesOnEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.DynamicPricesOnEnchants", false);

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
