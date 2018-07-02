REVOKE ALL PRIVILEGES ON * . * FROM 'NuskyCore'@'localhost';

REVOKE ALL PRIVILEGES ON `world` . * FROM 'NuskyCore'@'localhost';

REVOKE GRANT OPTION ON `world` . * FROM 'NuskyCore'@'localhost';

REVOKE ALL PRIVILEGES ON `characters` . * FROM 'NuskyCore'@'localhost';

REVOKE GRANT OPTION ON `characters` . * FROM 'NuskyCore'@'localhost';

REVOKE ALL PRIVILEGES ON `auth` . * FROM 'NuskyCore'@'localhost';

REVOKE GRANT OPTION ON `auth` . * FROM 'NuskyCore'@'localhost';

DROP USER 'NuskyCore'@'localhost';

DROP DATABASE IF EXISTS `world`;

DROP DATABASE IF EXISTS `characters`;

DROP DATABASE IF EXISTS `auth`;
