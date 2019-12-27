INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `BaseAttackTime`, `RangeAttackTime`, `unit_class`, `unit_flags`, `unit_flags2`, `type`, `type_flags`, `HealthModifier`, `ScriptName`) VALUES
(300000, 12345, '.::Template::.', '', 'Speak', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_Template'),
(300001, 12345, '.::BeastMastery::.', '', 'Speak', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_BeastMastery'),
(300002, 12345, '.::TOP::.', '', 'Speak', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_TOP'),
(300003, 12345, '.::Doctor::.', '', 'Speak', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_Doctor');
(300004, 12345, '.::Teleport::.', '', 'Speak', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_Teleport'),
(300005, 12345, '.::Mall Teleport::.', '', 'Speak', 0, 100, 100, 2, 35, 1, 0.8, 0, 2000, 0, 1, 0, 0, 7, 138936390, 100000, 'CreatureScript_Teleport_Mall');

INSERT INTO `command` VALUES
('character check bag', 2, 'Syntax: .character check bag [$target_player]\r #bagSlot 1 - 4'),
('character check work', 2, 'Syntax: .character check work [$target_player]\r\nShow known professions list for selected player');