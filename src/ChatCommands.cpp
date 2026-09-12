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
    NPCEnchanterEnhancedChatCommands() : CommandScript("NPCEnchanterEnchancedChatCommands") {}

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable commandTable =
        {
            { "NPCEE", HelpEnchanterCommand, SEC_PLAYER, Console::No },
            { "NPCEE spawn", SpawnEnchanterCommand, SEC_PLAYER , Console::No },
            { "NPCEE despawn", DespawnEnchanterCommand, SEC_PLAYER, Console::No },
            { "NPCEE help", HelpEnchanterCommand, SEC_PLAYER, Console::No },
            { "NPCEE config", ShowConfigurationEnchanterCommand, SEC_PLAYER, Console::No }
        };

        return commandTable;
    }

    static bool SpawnEnchanterCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        //Check if configured for anyone to be able to spawn, or if level is Gamemaster or above.
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
        float spawnOrientation = o + float(M_PI);

        if (Creature* enchanter = player->SummonCreature(NPCEnchanter_ID, spawnX, spawnY, z, spawnOrientation, TEMPSUMMON_TIMED_DESPAWN, NPCEnchanterEnhancedDespawnTimerInMS))
        {
            handler->SendSysMessage(enchanter->GetName() + " spawned. Despawns in " + std::to_string(NPCEnchanterEnhancedDespawnTimerInSeconds) + " seconds.");
            enchanter->Say("Greetings, champion! Ready to imbue your gear?", LANG_UNIVERSAL, 0);
            enchanter->HandleEmoteCommand(EMOTE_STATE_USE_STANDING);
        }

        return true;
    }

    static bool DespawnEnchanterCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        //Check if configured for anyone to be able to spawn, or if level is Gamemaster or above.
        if (!NPCEnchanterEnhancedSpawnableByAnyone && handler->GetSession()->GetSecurity() < SEC_GAMEMASTER)
            return false;

        Creature* enchanter = player->FindNearestCreature(NPCEnchanter_ID, 30.0f, true);
        if (enchanter)
        {
            if (enchanter->IsSummon() && enchanter->ToTempSummon()->GetSummonerGUID() == player->GetGUID())
            {
                enchanter->Say("Farewell, champion! Until next time.", LANG_UNIVERSAL, 0);
                enchanter->DespawnOrUnsummon(std::chrono::seconds(3));
                return true;
            }
        }

        handler->SendSysMessage("Enchanter entity not found.. You may need to be closer to it.");
        return true;
    }

    static bool HelpEnchanterCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        std::string creatureName = "";
        CreatureTemplate const* cInfo = sObjectMgr->GetCreatureTemplate(NPCEnchanter_ID);
        if (cInfo)
        {
            creatureName = cInfo->Name;
        }

        //Check if configured for anyone to be able to spawn, or if level is Gamemaster or above.
        if (!NPCEnchanterEnhancedSpawnableByAnyone && handler->GetSession()->GetSecurity() < SEC_GAMEMASTER)
        {
            handler->SendSysMessage("No commands available for your account level.");
            return true;
        }
        else
        {
            handler->SendSysMessage("=== NPC Enchanter Enhanced Commands ===");
            handler->SendSysMessage(".NPCEE spawn - " + (!creatureName.empty() ? creatureName : "Enchanter Xari"));
            handler->SendSysMessage(".NPCEE despawn - " + (!creatureName.empty() ? creatureName : "Enchanter Xari"));
            handler->SendSysMessage(".NPCEE help - Show this help menu.");
            handler->SendSysMessage(".NPCEE config - Show current configuration");
            return true;
        }

        handler->SendSysMessage("Could not find the enchanter.. ");
        return true;
    }

    static bool ShowConfigurationEnchanterCommand(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!player)
            return false;

        //Check if configured for anyone to be able to spawn, or if level is Gamemaster or above.
        if (!NPCEnchanterEnhancedSpawnableByAnyone && handler->GetSession()->GetSecurity() < SEC_GAMEMASTER)
        {
            handler->SendSysMessage("No commands available for your account level.");
            return true;
        }

        handler->SendSysMessage("=== Current NPC Enchanter Enhanced Configuration ===");
        handler->SendSysMessage("NPCEnchanterEnhanced.Enabled: " + std::to_string(NPCEnchanterEnhancedEnabled));
        handler->SendSysMessage("NPCEnchanterEnhanced.Announce: " + std::to_string(NPCEnchanterEnhancedAnnounce));
        handler->SendSysMessage("NPCEnchanterEnhanced.SpawnableByAnyone: " + std::to_string(NPCEnchanterEnhancedSpawnableByAnyone));
        handler->SendSysMessage("NPCEnchanterEnhanced.DespawnTimerInSeconds: " + std::to_string(NPCEnchanterEnhancedDespawnTimerInSeconds));
        handler->SendSysMessage("NPCEnchanterEnhanced.IndividualProgression: " + std::to_string(NPCEnchanterEnhancedIndividualProgression));
        handler->SendSysMessage("NPCEnchanterEnhanced.LockProfessionEnchants: " + std::to_string(NPCEnchanterEnhancedLockProfessionEnchants));
        handler->SendSysMessage("NPCEnchanterEnhanced.FreeEnchants: " + std::to_string(NPCEnchanterEnhancedFreeEnchants));
        handler->SendSysMessage("NPCEnchanterEnhanced.DynamicPricesOnEnchants: " + std::to_string(NPCEnchanterEnhancedDynamicPricesOnEnchants));
        return true;

    }
};

// Glöm inte att registrera skriptet i din loader-fil
void AddSC_NPCEnchanterEnhancedChatCommands()
{
    new NPCEnchanterEnhancedChatCommands();
}
