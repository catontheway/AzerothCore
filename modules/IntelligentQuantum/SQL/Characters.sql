-- TransMog
CREATE TABLE IF NOT EXISTS `custom_transmogrification` (
  `GUID` int(10) unsigned NOT NULL COMMENT 'Item guidLow',
  `FakeEntry` int(10) unsigned NOT NULL COMMENT 'Item entry',
  `Owner` int(10) unsigned NOT NULL COMMENT 'Player guidLow',
  PRIMARY KEY (`GUID`),
  KEY `Owner` (`Owner`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='6_2';

CREATE TABLE IF NOT EXISTS `custom_transmogrification_sets` (
  `Owner` int(10) unsigned NOT NULL COMMENT 'Player guidlow',
  `PresetID` tinyint(3) unsigned NOT NULL COMMENT 'Preset identifier',
  `SetName` text COMMENT 'SetName',
  `SetData` text COMMENT 'Slot1 Entry1 Slot2 Entry2',
  PRIMARY KEY (`Owner`,`PresetID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='6_1';

ALTER TABLE `guild` ADD `Level` INT(10) DEFAULT 0 NOT NULL AFTER `BankMoney`;
ALTER TABLE `guild` ADD `XP` TINYINT(3) DEFAULT 0 NOT NULL AFTER `Level`;
ALTER TABLE `guild` ADD `Kills` INT(10) DEFAULT 0 NOT NULL AFTER `XP`;
ALTER TABLE `guild` ADD `Points` INT(10) DEFAULT 0 NOT NULL AFTER `Kills`;