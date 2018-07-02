
-- ----------------------------
-- Table structure for pvpstats_battlegrounds
-- ----------------------------
DROP TABLE IF EXISTS `pvpstats_battlegrounds`;
CREATE TABLE `pvpstats_battlegrounds`  (
  `id` BIGINT(20) UNSIGNED NOT NULL AUTO_INCREMENT,
  `winner_faction` TINYINT(4) NOT NULL,
  `bracket_id` TINYINT(3) UNSIGNED NOT NULL,
  `type` TINYINT(3) UNSIGNED NOT NULL,
  `date` DATETIME NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = INNODB AUTO_INCREMENT = 11 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = COMPACT;

--
-- Dumping data for table `pvpstats_battlegrounds`
--

LOCK TABLES `pvpstats_battlegrounds` WRITE;
/*!40000 ALTER TABLE `pvpstats_battlegrounds` DISABLE KEYS */;
/*!40000 ALTER TABLE `pvpstats_battlegrounds` ENABLE KEYS */;
UNLOCK TABLES;

-- ----------------------------
-- Table structure for pvpstats_players
-- ----------------------------
DROP TABLE IF EXISTS `pvpstats_players`;
CREATE TABLE `pvpstats_players`  (
  `battleground_id` BIGINT(20) UNSIGNED NOT NULL,
  `character_guid` INT(10) UNSIGNED NOT NULL,
  `winner` BIT(1) NOT NULL,
  `score_killing_blows` MEDIUMINT(8) UNSIGNED NOT NULL,
  `score_deaths` MEDIUMINT(8) UNSIGNED NOT NULL,
  `score_honorable_kills` MEDIUMINT(8) UNSIGNED NOT NULL,
  `score_bonus_honor` MEDIUMINT(8) UNSIGNED NOT NULL,
  `score_damage_done` MEDIUMINT(8) UNSIGNED NOT NULL,
  `score_healing_done` MEDIUMINT(8) UNSIGNED NOT NULL,
  `attr_1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,
  `attr_2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,
  `attr_3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,
  `attr_4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,
  `attr_5` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`battleground_id`, `character_guid`) USING BTREE
) ENGINE = INNODB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = COMPACT;

--
-- Dumping data for table `pvpstats_players`
--

LOCK TABLES `pvpstats_players` WRITE;
/*!40000 ALTER TABLE `pvpstats_players` DISABLE KEYS */;
/*!40000 ALTER TABLE `pvpstats_players` ENABLE KEYS */;
UNLOCK TABLES;