
-- ----------------------------
-- Table structure for battleground_deserters
-- ----------------------------
DROP TABLE IF EXISTS `battleground_deserters`;
CREATE TABLE `battleground_deserters`  (
  `guid` int(10) UNSIGNED NOT NULL COMMENT 'characters.guid',
  `type` tinyint(3) UNSIGNED NOT NULL COMMENT 'type of the desertion',
  `datetime` datetime NOT NULL COMMENT 'datetime of the desertion'
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Compact;

--
-- Dumping data for table `battleground_deserters`
--

LOCK TABLES `battleground_deserters` WRITE;
/*!40000 ALTER TABLE `battleground_deserters` DISABLE KEYS */;
/*!40000 ALTER TABLE `battleground_deserters` ENABLE KEYS */;
UNLOCK TABLES;