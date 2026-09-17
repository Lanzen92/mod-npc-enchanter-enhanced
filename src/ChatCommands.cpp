#include "ConfigManager.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "Player.h"
#include "Creature.h"

uint32 NPCEnchanterEnhancedDespawnTimerInMS = NPCEnchanterEnhancedDespawnTimerInSeconds * 1000;

using namespace Acore::ChatCommands;

class NPCEnchanterEnhancedChatCommands : public CommandScript
{
public:
    NPCEnchanterEnhancedChatCommands() : CommandScript("NPCEnchanterEnhancedChatCommands") {}

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable commandTable =
        {
            { "NPCEE", HelpEnchanterCommand, SEC_PLAYER, Console::No },
            { "NPCEE spawn", SpawnEnchanterCommand, SEC_PLAYER , Console::No },
            { "NPCEE despawn", DespawnEnchanterCommand, SEC_PLAYER, Console::No },
            { "NPCEE help", HelpEnchanterCommand, SEC_PLAYER, Console::No },
            { "NPCEE config", ShowConfigurationEnchanterCommand, SEC_GAMEMASTER, Console::No },
            { "NPCEE reload", ReloadConfigurationEnchanterCommand, SEC_GAMEMASTER, Console::No }
        };

        return commandTable;
    }

    static bool SpawnEnchanterCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        //Check if configured for anyone to be able to spawn, or if level is Game master or above.
        if (!NPCEnchanterEnhancedSpawnableByAnyone && handler->GetSession()->GetSecurity() < SEC_GAMEMASTER)
            return false;

        if (player->IsInCombat())
        {
            handler->SendSysMessage("Cannot spawn while in combat.");
            return true;
        }

        float x = player->GetPositionX();
        float y = player->GetPositionY();
        float z = player->GetPositionZ();
        float o = player->GetOrientation();

        //2.5 yards in front of the player.
        float distance = 2.5f;
        float spawnX = x + distance * cos(o);
        float spawnY = y + distance * sin(o);

        //Rotate facing the player
        float spawnOrientation = o + static_cast<float>(M_PI);

        if (Creature* enchanter = player->SummonCreature(NPCEnchanterID, spawnX, spawnY, z, spawnOrientation, TEMPSUMMON_TIMED_DESPAWN, NPCEnchanterEnhancedDespawnTimerInMS))
        {
            handler->SendSysMessage(enchanter->GetName() + " spawned. Despawns in " + std::to_string(NPCEnchanterEnhancedDespawnTimerInSeconds) + " seconds.");
            enchanter->Say("Greetings, champion! Ready to imbue your gear?", LANG_UNIVERSAL, nullptr);
            enchanter->HandleEmoteCommand(EMOTE_STATE_USE_STANDING);
        }

        return true;
    }

    static bool DespawnEnchanterCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        //Check if configured for anyone to be able to spawn, or if level is Game master or above.
        if (!NPCEnchanterEnhancedSpawnableByAnyone && handler->GetSession()->GetSecurity() < SEC_GAMEMASTER)
            return false;

        if (Creature* enchanter = player->FindNearestCreature(NPCEnchanterID, 30.0f, true))
        {
            if (enchanter->IsSummon() && enchanter->ToTempSummon()->GetSummonerGUID() == player->GetGUID())
            {
                enchanter->Say("Farewell, champion! Until next time.", LANG_UNIVERSAL, nullptr);
                enchanter->DespawnOrUnsummon(std::chrono::seconds(3));
                return true;
            }
        }

        handler->SendSysMessage("Enchanter entity not found.. You may need to be closer to him.");
        return true;
    }

    static bool HelpEnchanterCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        std::string creatureName = "";
        if (CreatureTemplate const* cInfo = sObjectMgr->GetCreatureTemplate(NPCEnchanterID))
        {
            creatureName = cInfo->Name;
        }

        handler->SendSysMessage("=== NPC Enchanter Enhanced Commands ===");
        handler->SendSysMessage(".NPCEE spawn - " + (!creatureName.empty() ? creatureName : "Enchanter Xari"));
        handler->SendSysMessage(".NPCEE despawn - " + (!creatureName.empty() ? creatureName : "Enchanter Xari"));
        handler->SendSysMessage(".NPCEE help - Show this help menu.");

        //Check if configured for anyone to be able to spawn, or if level is Game master or above.
        if (!NPCEnchanterEnhancedSpawnableByAnyone && handler->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
        {
            handler->SendSysMessage(".NPCEE config - Show current configuration");
            handler->SendSysMessage(".NPCEE reload - Reload configuration");
            return true;
        }

        return true;
    }

    //Todo Update...
    static bool ShowConfigurationEnchanterCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        //Check if configured for anyone to be able to spawn, or if level is Game master or above.
        if (handler->GetSession()->GetSecurity() < SEC_GAMEMASTER)
        {
            handler->SendSysMessage("No commands available for your account level.");
            return true;
        }

        handler->SendSysMessage("=== Current NPC Enchanter Enhanced Configuration ===");
        handler->SendSysMessage("NPCEnchanterEnhanced.Enabled: " + std::to_string(NPCEnchanterEnhancedEnabled));
        handler->SendSysMessage("NPCEnchanterEnhanced.Announce: " + std::to_string(NPCEnchanterEnhancedAnnounce));

        handler->SendSysMessage("===  NPC  ===");
        handler->SendSysMessage("NPCEnchanterEnhanced.SpawnableByAnyone: " + std::to_string(NPCEnchanterEnhancedSpawnableByAnyone));
        handler->SendSysMessage("NPCEnchanterEnhanced.DespawnTimerInSeconds: " + std::to_string(NPCEnchanterEnhancedDespawnTimerInSeconds));

        handler->SendSysMessage("===  Filtering  ===");
        handler->SendSysMessage("NPCEnchanterEnhanced.IgnoreProfessionRequirements: " + std::to_string(NPCEnchanterEnhancedIgnoreProfessionRequirements));
        handler->SendSysMessage("NPCEnchanterEnhanced.IgnoreLevelRequirements: " + std::to_string(NPCEnchanterEnhancedIgnoreLevelRequirements));
        handler->SendSysMessage("NPCEnchanterEnhanced.IgnoreItemLevelRequirements: " + std::to_string(NPCEnchanterEnhancedIgnoreItemLevelRequirements));
        handler->SendSysMessage("NPCEnchanterEnhanced.IgnoreClassRequirements: " + std::to_string(NPCEnchanterEnhancedIgnoreClassRequirements));
        handler->SendSysMessage("NPCEnchanterEnhanced.TiersToShow: " + sConfigMgr->GetOption<std::string>("NPCEnchanterEnhanced.TiersToShow", "Leveling, PreRaid, Raid"));
        handler->SendSysMessage("NPCEnchanterEnhanced.HideUnavailableEnchants: " + std::to_string(NPCEnchanterEnhancedHideUnavailableEnchants));

        handler->SendSysMessage("===  Phases  ===");
        handler->SendSysMessage("NPCEnchanterEnhanced.IndividualProgression: " + std::to_string(NPCEnchanterEnhancedIndividualProgression));
        handler->SendSysMessage("NPCEnchanterEnhanced.Phase: " + std::to_string(NPCEnchanterEnhancedPhase));

        handler->SendSysMessage("===  Price  ===");
        handler->SendSysMessage("NPCEnchanterEnhanced.FreeEnchants: " + std::to_string(NPCEnchanterEnhancedFreeEnchants));
        handler->SendSysMessage("NPCEnchanterEnhanced.DynamicPricesOnEnchants: " + std::to_string(NPCEnchanterEnhancedDynamicPricesOnEnchants));

        std::string multipliers = "";




        return true;
    }

    static bool ReloadConfigurationEnchanterCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        if (!sConfigMgr->Reload())
        {
            handler->SendSysMessage("Failed to reload configuration file.");
            return false;
        }

        LoadEnchantConfig(true);

        handler->SendSysMessage("NPC Enchanter Enhanced configuration reloaded successfully.");
        return true;
    }
};

void AddSC_NPCEnchanterEnhancedChatCommands()
{
    new NPCEnchanterEnhancedChatCommands();
}
