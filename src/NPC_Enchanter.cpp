
#include "Cell.h"
#include "CellImpl.h"
#include "Chat.h"
#include "CombatAI.h"
#include "Configuration/Config.h"
#include "DBCStores.h"
#include "DBCStructure.h"
#include "GameEventMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "GameObject.h"
#include "InstanceScript.h"
#include "ObjectMgr.h"
#include "PassiveAI.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Unit.h"
#include "EnchantTypes.h"

bool NPCEnchanterEnhancedEnabled;
bool NPCEnchanterEnhancedAnnounce;
uint32 NPCEnchanter_ID = 602050;

uint32 MainMenuAction = 999;
uint32 WeaponMenuAction = 998;
uint32 ArmorMenuAction = 997;


class NPCEnchanterEnhancedNPCConfig : public WorldScript {
    public:
    NPCEnchanterEnhancedNPCConfig() : WorldScript("NPCEnchanterEnhancedConfig_conf", {
        WORLDHOOK_ON_BEFORE_CONFIG_LOAD
    }) { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            NPCEnchanterEnhancedEnabled = sConfigMgr->GetOption<bool>("Enable", 1);
            NPCEnchanterEnhancedAnnounce = sConfigMgr->GetOption<bool>("Announce", 1);
        }
    }
};
class NPCEnchanterEnchancedAnnounce : public PlayerScript {

    public:

    NPCEnchanterEnchancedAnnounce() : PlayerScript("NPCEnchanterEnchancedAnnounce", {
        PLAYERHOOK_ON_LOGIN
    }) {}

    void OnPlayerLogin(Player* player) {
        if (NPCEnchanterEnhancedAnnounce)
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the NPCEnchanterEnchanced module.");
    }
};


class NPCEnchanterEnhanced : public CreatureScript {
    public:
    NPCEnchanterEnhanced() : CreatureScript("NPCEnchanterEnhanced") {
    }

    bool OnGossipHello(Player* player, Creature* creature) override {

        if (!NPCEnchanterEnhancedEnabled)
            return false;

        ClearGossipMenuFor(player);

        AddGossipItemFor(player, 1, "|TInterface/ICONS/Inv_axe_113:24:24:-18|tWeapon enchantments",
            GOSSIP_SENDER_MAIN, EnchantCategory::Weapon);

        AddGossipItemFor(player, 1, "|TInterface/ICONS/Inv_shield_71:24:24:-18|tShield enchantments",
            GOSSIP_SENDER_MAIN, EnchantCategory::Shield);

        AddGossipItemFor(player, 1, "|TInterface/ICONS/inv_chest_cloth_04:24:24:-18|tArmor enchantments",
            GOSSIP_SENDER_MAIN, EnchantCategory::Armor);

        SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override {

        if (!NPCEnchanterEnhancedEnabled)
            return false;

        ClearGossipMenuFor(player);

        switch (action)
        {
            case EnchantCategory::Weapon:

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_sword_39:24:24:-18|t1H Melee",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_1H_Melee);

                //Check if able to dual wield.
                if (player->HasSpell(674))
                {
                    AddGossipItemFor(player, 1,
                        "|TInterface/ICONS/inv_weapon_shortblade_03:24:24:-18|t1H Melee Offhand",
                        GOSSIP_SENDER_MAIN,
                        EnchantSubType::Weapon_1H_Melee_Offhand);
                }

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_axe_09:24:24:-18|t2H Melee",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_2H_Melee);

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_weapon_shortblade_37:24:24:-18|t1H Caster",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_1H_Caster);

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_staff_13:24:24:-18|t2H Caster",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_2H_Caster);

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_weapon_bow_11:24:24:-18|tRanged",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_Ranged);


                ////
                AddGossipItemFor(player, GOSSIP_ICON_CHAT,
                    "<- Back to main menu", GOSSIP_SENDER_MAIN, MainMenuAction);
                SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
                break;
            case EnchantCategory::Shield



                ////
                AddGossipItemFor (player, GOSSIP_ICON_CHAT,
                    "<- Back to main menu", GOSSIP_SENDER_MAIN, MainMenuAction);
                SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
                break;
            case EnchantCategory::Armor:

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_sword_39:24:24:-18|tHelm",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Helm);

                //Gate behind ZG-phase
                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_sword_39:24:24:-18|tShoulders",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Shoulders);

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_sword_39:24:24:-18|tCloak",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Cloak);

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_sword_39:24:24:-18|tChest",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Chest);

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_sword_39:24:24:-18|tBracers",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Bracers);

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_sword_39:24:24:-18|tGloves",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Gloves);

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_sword_39:24:24:-18|tLegs",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Legs);

                AddGossipItemFor(player, 1,
                    "|TInterface/ICONS/inv_sword_39:24:24:-18|tBoots",
                    GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Boots);

                //Gate behind phase and check profession
                if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) == 450)
                {
                    AddGossipItemFor(player, 1, "|TInterface/ICONS/inv_sword_39:24:24:-18|tRing",
                        GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Ring);
                }



                ////
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "<- Back to main menu", GOSSIP_SENDER_MAIN, MainMenuAction);
                SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
                break;

            //Todo when menus are done.
            case WeaponMenuAction:
            case ArmorMenuAction:
            case MainMenuAction: //Back to main

                AddGossipItemFor(player, 1, "|TInterface/ICONS/Inv_axe_113:24:24:-18|tWeapon enchantments",
                    GOSSIP_SENDER_MAIN, EnchantCategory::Weapon);

                AddGossipItemFor(player, 1, "|TInterface/ICONS/Inv_shield_71:24:24:-18|tShield enchantments",
                    GOSSIP_SENDER_MAIN, EnchantCategory::Shield);

                AddGossipItemFor(player, 1, "|TInterface/ICONS/inv_chest_cloth_04:24:24:-18|tArmor enchantments",
                    GOSSIP_SENDER_MAIN, EnchantCategory::Armor);

                ////
                SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
                break;
            default:
                CloseGossipMenuFor(player);
                return true;

        }

        return true;
    }
};

void AddSC_NPCEnchanterEnhanced()
{
    new NPCEnchanterEnhancedNPCConfig();
    new NPCEnchanterEnchancedAnnounce();
    new NPCEnchanterEnhanced();
}

// class NPCEnchanterEnhanced : public CreatureScript {
//     public:
//     NPCEnchanterEnhanced() : CreatureScript("NPCEnchanterEnhanced") {
//     }
//
//     bool OnGossipHello(Player* player, Creature* creature) override {
//
//         if (!NPCEnchanterEnhancedEnabled)
//             return false;
//
//         ClearGossipMenuFor(player);
//
//         AddGossipItemFor(player, 1, "|TInterface/ICONS/Inv_axe_113:24:24:-18|tWeapon enchantments",
//             GOSSIP_SENDER_MAIN, EnchantCategory::Weapon);
//
//         AddGossipItemFor(player, 1, "|TInterface/ICONS/Inv_shield_71:24:24:-18|tShield enchantments",
//             GOSSIP_SENDER_MAIN, EnchantCategory::Shield);
//
//         AddGossipItemFor(player, 1, "|TInterface/ICONS/inv_chest_cloth_04:24:24:-18|tArmor enchantments",
//             GOSSIP_SENDER_MAIN, EnchantCategory::Armor);
//
//         SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
//         return true;
//     }
//
//     bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override {
//
//         if (!NPCEnchanterEnhancedEnabled)
//             return false;
//
//         ClearGossipMenuFor(player);
//
//         switch (action)
//         {
//             case EnchantCategory::Weapon:
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_sword_39:24:24:-18|t1H Melee",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_1H_Melee);
//
//                 //Check if able to dual wield.
//                 if (player->HasSpell(674))
//                 {
//                     AddGossipItemFor(player, 1,
//                         "|TInterface/ICONS/inv_weapon_shortblade_03:24:24:-18|t1H Melee Offhand",
//                         GOSSIP_SENDER_MAIN,
//                         EnchantSubType::Weapon_1H_Melee_Offhand);
//                 }
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_axe_09:24:24:-18|t2H Melee",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_2H_Melee);
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_weapon_shortblade_37:24:24:-18|t1H Caster",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_1H_Caster);
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_staff_13:24:24:-18|t2H Caster",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_2H_Caster);
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_weapon_bow_11:24:24:-18|tRanged",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Weapon_Ranged);
//
//
//                 ////
//                 AddGossipItemFor(player, GOSSIP_ICON_CHAT,
//                     "<- Back to main menu", GOSSIP_SENDER_MAIN, MainMenuAction);
//                 SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
//                 break;
//             case EnchantCategory::Shield
//
//
//
//                 ////
//                 AddGossipItemFor (player, GOSSIP_ICON_CHAT,
//                     "<- Back to main menu", GOSSIP_SENDER_MAIN, MainMenuAction);
//                 SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
//                 break;
//             case EnchantCategory::Armor:
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_sword_39:24:24:-18|tHelm",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Helm);
//
//                 //Gate behind ZG-phase
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_sword_39:24:24:-18|tShoulders",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Shoulders);
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_sword_39:24:24:-18|tCloak",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Cloak);
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_sword_39:24:24:-18|tChest",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Chest);
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_sword_39:24:24:-18|tBracers",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Bracers);
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_sword_39:24:24:-18|tGloves",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Gloves);
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_sword_39:24:24:-18|tLegs",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Legs);
//
//                 AddGossipItemFor(player, 1,
//                     "|TInterface/ICONS/inv_sword_39:24:24:-18|tBoots",
//                     GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Boots);
//
//                 //Gate behind phase and check profession
//                 if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) == 450)
//                 {
//                     AddGossipItemFor(player, 1, "|TInterface/ICONS/inv_sword_39:24:24:-18|tRing",
//                         GOSSIP_SENDER_MAIN, EnchantSubType::Armor_Ring);
//                 }
//
//
//
//                 ////
//                 AddGossipItemFor(player, GOSSIP_ICON_CHAT, "<- Back to main menu", GOSSIP_SENDER_MAIN, MainMenuAction);
//                 SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
//                 break;
//
//             //Todo when menus are done.
//             case WeaponMenuAction:
//             case ArmorMenuAction:
//             case MainMenuAction: //Back to main
//
//                 AddGossipItemFor(player, 1, "|TInterface/ICONS/Inv_axe_113:24:24:-18|tWeapon enchantments",
//                     GOSSIP_SENDER_MAIN, EnchantCategory::Weapon);
//
//                 AddGossipItemFor(player, 1, "|TInterface/ICONS/Inv_shield_71:24:24:-18|tShield enchantments",
//                     GOSSIP_SENDER_MAIN, EnchantCategory::Shield);
//
//                 AddGossipItemFor(player, 1, "|TInterface/ICONS/inv_chest_cloth_04:24:24:-18|tArmor enchantments",
//                     GOSSIP_SENDER_MAIN, EnchantCategory::Armor);
//
//                 ////
//                 SendGossipMenuFor(player, NPCEnchanter_ID, creature->GetGUID());
//                 break;
//             default:
//                 CloseGossipMenuFor(player);
//                 return true;
//
//         }
//
//         return true;
//     }
// };
