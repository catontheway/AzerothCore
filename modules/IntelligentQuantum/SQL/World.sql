-- Creature Template
INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `BaseAttackTime`, `RangeAttackTime`, `unit_class`, `unit_flags`, `unit_flags2`, `type`, `type_flags`, `HealthModifier`, `ScriptName`) VALUES
(200000, 12345, 'Template', '', 'Trainer', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_Template'),
(200001, 12345, 'BeastMastery', '', 'Gunner', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_BeastMastery'),
(200002, 12345, 'TOP', '', 'Attack', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_TOP'),
(200003, 12345, 'Doctor', '', 'Driver', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_Doctor'),
(200004, 12345, 'Teleport', '', 'Taxi', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_Teleport'),
(200005, 12345, 'Transmogrifier', '', 'Interact', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_Transmogrifier'),
(200006, 12345, 'Ex-Changer', '', 'Buy', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_ExChanger'),
(200007, 12345, 'Character Tools', '', 'Buy', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_CharacterTools');
(200009, 12345, 'Solo 3v3', '', 'Buy', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_Solo3v3');

-- Gurubashi Invisible
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (200008, 0, 0, 0, 0, 0, 1126, 11686, 0, 0, 'Gurubashi Invisible', '', '', 0, 1, 1, 0, 35, 0, 1, 1.14286, 1, 0, 2, 2, 0, 24, 1, 2000, 2000, 1, 33554432, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 1, 0, 128, 'CreatureScript_Gurubashi', 12340);

-- Commands
INSERT INTO `command` VALUES
('character check bag', 3, 'Syntax: .character check bag [$target_player]\r #bagSlot 1 - 4'),
('character check work', 3, 'Syntax: .character check work [$target_player]\r\nShow known professions list for selected player');

-- TransMog
SET @TEXT_ID := 601083;
DELETE FROM `npc_text` WHERE `ID` IN  (@TEXT_ID,@TEXT_ID+1);
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES
(@TEXT_ID, 'Transmogrification allows you to change how your items look like without changing the stats of the items.\r\nItems used in transmogrification are no longer refundable, tradeable and are bound to you.\r\nUpdating a menu updates the view and prices.\r\n\r\nNot everything can be transmogrified with eachother.\r\nRestrictions include but are not limited to:\r\nOnly armor and weapons can be transmogrified\r\nGuns, bows and crossbows can be transmogrified with eachother\r\nFishing poles can not be transmogrified\r\nYou must be able to equip both items used in the process.\r\n\r\nTransmogrifications stay on your items as long as you own them.\r\nIf you try to put the item in guild bank or mail it to someone else, the transmogrification is stripped.\r\n\r\nYou can also remove transmogrifications for free at the transmogrifier.'),
(@TEXT_ID+1, 'You can save your own transmogrification sets.\r\n\r\nTo save, first you must transmogrify your equipped items.\r\nThen when you go to the set management menu and go to save set menu,\r\nall items you have transmogrified are displayed so you see what you are saving.\r\nIf you think the set is fine, you can click to save the set and name it as you wish.\r\n\r\nTo use a set you can click the saved set in the set management menu and then select use set.\r\nIf the set has a transmogrification for an item that is already transmogrified, the old transmogrification is lost.\r\nNote that same transmogrification restrictions apply when trying to use a set as in normal transmogrification.\r\n\r\nTo delete a set you can go to the set\'s menu and select delete set.');

-- Acore String
SET @STRING_ENTRY := 11100;
DELETE FROM `acore_string` WHERE `entry` IN  (@STRING_ENTRY+0,@STRING_ENTRY+1,@STRING_ENTRY+2,@STRING_ENTRY+3,@STRING_ENTRY+4,@STRING_ENTRY+5,@STRING_ENTRY+6,@STRING_ENTRY+7,@STRING_ENTRY+8,@STRING_ENTRY+9,@STRING_ENTRY+10);
INSERT INTO `acore_string` (`entry`, `content_default`) VALUES
(@STRING_ENTRY+0, 'Item transmogrified'),
(@STRING_ENTRY+1, 'Equipment slot is empty'),
(@STRING_ENTRY+2, 'Invalid source item selected'),
(@STRING_ENTRY+3, 'Source item does not exist'),
(@STRING_ENTRY+4, 'Destination item does not exist'),
(@STRING_ENTRY+5, 'Selected items are invalid'),
(@STRING_ENTRY+6, 'Not enough money'),
(@STRING_ENTRY+7, 'You don\'t have enough tokens'),
(@STRING_ENTRY+8, 'Transmogrifications removed'),
(@STRING_ENTRY+9, 'There are no transmogrifications'),
(@STRING_ENTRY+10, 'Invalid name inserted'),
(50000, '%s %s %s');
