-- --------------------------------------------------------------------------------------
--	ENCHANTER - 602050
-- --------------------------------------------------------------------------------------
SET
@Entry 		:= 602050,
@Model 		:= 25965, -- Kirin Tor Mage
@Weapon     := 29981, -- Ethereum Life-Staff
@Name 		:= "Enchanter Xari",
@Title 		:= "Enchants",
@Icon 		:= "Speak",
@GossipMenu := 0,
@MinLevel 	:= 80,
@MaxLevel 	:= 80,
@Faction 	:= 35,
@NPCFlag 	:= 1,
@Scale		:= 1.0,
@Type 		:= 7,
@TypeFlags 	:= 0,
@FlagsExtra := 2,
@AIName		:= "",
@Script 	:= "NPCEnchanterEnhanced";

-- NPC CREATURE
DELETE FROM creature_template WHERE entry = @Entry;
INSERT INTO creature_template (`entry`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `AiName`, `ScriptName`) VALUES
    (@Entry, @Name, @Title, @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1.14286, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @AIName, @Script);

-- NPC MODEL
DELETE FROM `creature_template_model` WHERE `CreatureID` = @Entry;
INSERT INTO `creature_template_model` (`CreatureID`, `Idx`, `CreatureDisplayID`, `DisplayScale`, `Probability`, `VerifiedBuild`) VALUES
    (@Entry, 0, @Model, 1, 1, 0);

-- NPC EQUIPPED
DELETE FROM `creature_equip_template` WHERE `CreatureID`=@Entry AND `ID`=1;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`, `VerifiedBuild`) VALUES
    (@Entry, 1, @Weapon, 0, 0, 0);

-- NPC TEXT
DELETE FROM `npc_text` WHERE `ID` BETWEEN @Entry AND @Entry + 2;
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES
     (@Entry,     'Knowledge is power, $N, but properly enchanted equipment is its own distinct advantage.$B$BJust remember: I only work on what you have equipped right now—bring it worn, not tucked away in a bag.$B$BSpeak your needs..'),
     (@Entry + 1, 'Select an equipment slot or weapon type to view available enhancements, $N.$B$BAnd as i just said.. I only work on what you have equipped right now.$B$BDisabled categories indicate missing requirements.'),
     (@Entry + 2, 'Choose your preferred tier of power carefully, $N. Quality has its price.');
