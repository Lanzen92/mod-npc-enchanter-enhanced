#include "ConfigManager.h"
#include "Define.h"
#include "Config.h"
#include "ScriptMgr.h"

extern const uint32 NPCEnchanter_ID = 602050;
bool NPCEnchanterEnhancedEnabled = false;
bool NPCEnchanterEnhancedAnnounce= false;
bool NPCEnchanterEnhancedSpawnableByAnyone = false;
uint32 NPCEnchanterEnhancedDespawnTimerInSeconds = 120;
bool NPCEnchanterEnhancedIndividualProgression = false;
bool NPCEnchanterEnhancedLockProfessionEnchants = false;
bool NPCEnchanterEnhancedFreeEnchants = false;
bool NPCEnchanterEnhancedDynamicPricesOnEnchants = false;

void LoadEnchantConfig(bool /*reload*/)
{
    NPCEnchanterEnhancedEnabled = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.Enabled", true);
    NPCEnchanterEnhancedAnnounce = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.Announce", true);
    NPCEnchanterEnhancedSpawnableByAnyone = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.SpawnableByAnyone", true);
    NPCEnchanterEnhancedDespawnTimerInSeconds = sConfigMgr->GetOption<uint32>("NPCEnchanterEnhanced.DespawnTimerInSeconds", 120);
    NPCEnchanterEnhancedIndividualProgression = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.IndividualProgression", false);
    NPCEnchanterEnhancedLockProfessionEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.LockProfessionEnchants", false);
    NPCEnchanterEnhancedFreeEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.FreeEnchants", false);
    NPCEnchanterEnhancedDynamicPricesOnEnchants = sConfigMgr->GetOption<bool>("NPCEnchanterEnhanced.DynamicPricesOnEnchants", false);
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
