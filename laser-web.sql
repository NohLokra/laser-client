-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Client :  127.0.0.1
-- Généré le :  Jeu 13 Octobre 2016 à 05:55
-- Version du serveur :  5.6.17
-- Version de PHP :  5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données :  `laser-web`
--

-- --------------------------------------------------------

--
-- Structure de la table `acl`
--

CREATE TABLE IF NOT EXISTS `acl` (
  `ai` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `action_id` int(10) unsigned NOT NULL,
  `user_id` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`ai`),
  KEY `action_id` (`action_id`),
  KEY `user_id` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `acl_actions`
--

CREATE TABLE IF NOT EXISTS `acl_actions` (
  `action_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `action_code` varchar(100) NOT NULL COMMENT 'No periods allowed!',
  `action_desc` varchar(100) NOT NULL COMMENT 'Human readable description',
  `category_id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`action_id`),
  KEY `category_id` (`category_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `acl_categories`
--

CREATE TABLE IF NOT EXISTS `acl_categories` (
  `category_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `category_code` varchar(100) NOT NULL COMMENT 'No periods allowed!',
  `category_desc` varchar(100) NOT NULL COMMENT 'Human readable description',
  PRIMARY KEY (`category_id`),
  UNIQUE KEY `category_code` (`category_code`),
  UNIQUE KEY `category_desc` (`category_desc`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `auth_sessions`
--

CREATE TABLE IF NOT EXISTS `auth_sessions` (
  `id` varchar(40) NOT NULL,
  `user_id` int(10) unsigned NOT NULL,
  `login_time` datetime DEFAULT NULL,
  `modified_at` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `ip_address` varchar(45) NOT NULL,
  `user_agent` varchar(60) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Contenu de la table `auth_sessions`
--

INSERT INTO `auth_sessions` (`id`, `user_id`, `login_time`, `modified_at`, `ip_address`, `user_agent`) VALUES
('fb78c952ce4d0071283862639b7a599cc069225a', 1177090485, '2016-10-10 05:33:40', '2016-10-10 03:33:40', '127.0.0.1', 'Chrome 50.0.2661.102 on Windows 7');

-- --------------------------------------------------------

--
-- Structure de la table `centers`
--

CREATE TABLE IF NOT EXISTS `centers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `manager_id` int(10) unsigned NOT NULL,
  `telephone` int(11) NOT NULL,
  `email` varchar(50) NOT NULL,
  `street` varchar(100) NOT NULL,
  `zip_code` varchar(15) NOT NULL,
  `country` varchar(40) NOT NULL,
  `city` varchar(50) NOT NULL,
  `facebook` varchar(50) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_center_manager_id` (`manager_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `ci_sessions`
--

CREATE TABLE IF NOT EXISTS `ci_sessions` (
  `id` varchar(40) NOT NULL,
  `ip_address` varchar(45) NOT NULL,
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0',
  `data` blob NOT NULL,
  PRIMARY KEY (`id`),
  KEY `ci_sessions_timestamp` (`timestamp`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `denied_access`
--

CREATE TABLE IF NOT EXISTS `denied_access` (
  `ai` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ip_address` varchar(45) NOT NULL,
  `time` datetime NOT NULL,
  `reason_code` tinyint(1) unsigned DEFAULT '0',
  PRIMARY KEY (`ai`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

-- --------------------------------------------------------

--
-- Structure de la table `games`
--

CREATE TABLE IF NOT EXISTS `games` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `timestamp` timestamp NOT NULL COMMENT 'Date et heure de début de la partie',
  `nb_players` int(11) NOT NULL COMMENT 'Nombre total de joueurs',
  `name` varchar(10) NOT NULL COMMENT 'TEST|TEAM|....',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Table qui contient toutes les parties qui se sont jouées' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `games_hits`
--

CREATE TABLE IF NOT EXISTS `games_hits` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `player_id` int(11) NOT NULL COMMENT 'Id du joueur qui a reçu la touche',
  `player_name` varchar(12) NOT NULL COMMENT 'Nom du joueur qui a mis la touche',
  `rear` int(11) NOT NULL,
  `front` int(11) NOT NULL,
  `shoulder` int(11) NOT NULL,
  `laser` int(11) NOT NULL,
  `total` int(11) NOT NULL,
  `player_team` varchar(10) NOT NULL COMMENT 'Couleur du joueur qui a mis la touche',
  PRIMARY KEY (`id`),
  KEY `FK_hit_player_id` (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Table qui contient les touches reçues lors des parties' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `games_players`
--

CREATE TABLE IF NOT EXISTS `games_players` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `team_id` int(11) NOT NULL,
  `score` int(11) NOT NULL,
  `ratio` int(11) NOT NULL,
  `pack_number` int(11) NOT NULL,
  `nb_shots` int(11) NOT NULL,
  `ranking` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_user_id` (`user_id`),
  KEY `FK_team_id` (`team_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `games_shots`
--

CREATE TABLE IF NOT EXISTS `games_shots` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `player_id` int(11) NOT NULL COMMENT 'id du joueur qui a touché',
  `player_name` varchar(12) NOT NULL COMMENT 'Nom du joueur touché',
  `rear` int(11) NOT NULL,
  `shoulder` int(11) NOT NULL,
  `front` int(11) NOT NULL,
  `laser` int(11) NOT NULL,
  `total` int(11) NOT NULL,
  `player_team` varchar(10) NOT NULL COMMENT 'Team du joueur touché',
  PRIMARY KEY (`id`),
  KEY `FK_shot_player_id` (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `games_teams`
--

CREATE TABLE IF NOT EXISTS `games_teams` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `game_id` int(11) NOT NULL,
  `color` varchar(10) NOT NULL,
  `score` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_game_id` (`game_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `ips_on_hold`
--

CREATE TABLE IF NOT EXISTS `ips_on_hold` (
  `ai` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ip_address` varchar(45) NOT NULL,
  `time` datetime NOT NULL,
  PRIMARY KEY (`ai`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

-- --------------------------------------------------------

--
-- Structure de la table `login_errors`
--

CREATE TABLE IF NOT EXISTS `login_errors` (
  `ai` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username_or_email` varchar(255) NOT NULL,
  `ip_address` varchar(45) NOT NULL,
  `time` datetime NOT NULL,
  PRIMARY KEY (`ai`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=48 ;

-- --------------------------------------------------------

--
-- Structure de la table `players`
--

CREATE TABLE IF NOT EXISTS `players` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nickname` varchar(15) NOT NULL,
  `user_id` int(10) unsigned NOT NULL,
  `team_id` int(11) DEFAULT NULL,
  `email_hidden` tinyint(1) NOT NULL DEFAULT '0',
  `facebook` varchar(50) DEFAULT NULL,
  `twitter` varchar(50) DEFAULT NULL,
  `skype` varchar(50) DEFAULT NULL,
  `first_name` varchar(30) DEFAULT NULL,
  `last_name` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_player_user_id` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `tokens`
--

CREATE TABLE IF NOT EXISTS `tokens` (
  `username` varchar(12) NOT NULL,
  `user_id` int(11) unsigned NOT NULL,
  `token` varchar(64) NOT NULL,
  KEY `FK_tokens_user_id` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `tokens`
--

INSERT INTO `tokens` (`username`, `user_id`, `token`) VALUES
('Emile', 1177090485, 'f95d4c7b61bd649cbd6cbb724b299ccc3514b7d341af3df44063f6bb6f0e430f');

-- --------------------------------------------------------

--
-- Structure de la table `username_or_email_on_hold`
--

CREATE TABLE IF NOT EXISTS `username_or_email_on_hold` (
  `ai` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username_or_email` varchar(255) NOT NULL,
  `time` datetime NOT NULL,
  PRIMARY KEY (`ai`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `user_id` int(10) unsigned NOT NULL,
  `username` varchar(12) DEFAULT NULL,
  `email` varchar(255) NOT NULL,
  `auth_level` tinyint(3) unsigned NOT NULL,
  `banned` enum('0','1') NOT NULL DEFAULT '0',
  `passwd` varchar(60) NOT NULL,
  `passwd_recovery_code` varchar(60) DEFAULT NULL,
  `passwd_recovery_date` datetime DEFAULT NULL,
  `passwd_modified_at` datetime DEFAULT NULL,
  `last_login` datetime DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `modified_at` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `email` (`email`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Contenu de la table `users`
--

INSERT INTO `users` (`user_id`, `username`, `email`, `auth_level`, `banned`, `passwd`, `passwd_recovery_code`, `passwd_recovery_date`, `passwd_modified_at`, `last_login`, `created_at`, `modified_at`) VALUES
(734104008, 'Zozo', 'zozoleclown1@gmail.com', 9, '0', '$2y$11$BNNu8gjqOqczPN3A6ha8buUPivLo5.bl2Q7DsYoWOtbPkdBDotxZW', NULL, NULL, NULL, NULL, '2016-10-05 01:36:54', '2016-10-04 23:36:54'),
(1177090485, 'Emile', 'pierrick.couget@gmail.com', 6, '0', '$2y$11$id0Sm24PfzsY0MLSu4lsg.I/hM.MmGN0Mt01dwisqRhUJ/sJB5fg2', NULL, NULL, NULL, '2016-10-10 05:33:40', '2016-10-10 05:15:52', '2016-10-10 03:34:28');

--
-- Déclencheurs `users`
--
DROP TRIGGER IF EXISTS `ca_passwd_trigger`;
DELIMITER //
CREATE TRIGGER `ca_passwd_trigger` BEFORE UPDATE ON `users`
 FOR EACH ROW BEGIN
    IF ((NEW.passwd <=> OLD.passwd) = 0) THEN
        SET NEW.passwd_modified_at = NOW();
    END IF;
END
//
DELIMITER ;

--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `acl`
--
ALTER TABLE `acl`
  ADD CONSTRAINT `acl_ibfk_1` FOREIGN KEY (`action_id`) REFERENCES `acl_actions` (`action_id`) ON DELETE CASCADE,
  ADD CONSTRAINT `acl_ibfk_2` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON DELETE CASCADE;

--
-- Contraintes pour la table `acl_actions`
--
ALTER TABLE `acl_actions`
  ADD CONSTRAINT `acl_actions_ibfk_1` FOREIGN KEY (`category_id`) REFERENCES `acl_categories` (`category_id`) ON DELETE CASCADE;

--
-- Contraintes pour la table `centers`
--
ALTER TABLE `centers`
  ADD CONSTRAINT `FK_center_manager_id` FOREIGN KEY (`manager_id`) REFERENCES `users` (`user_id`);

--
-- Contraintes pour la table `games_hits`
--
ALTER TABLE `games_hits`
  ADD CONSTRAINT `FK_hit_player_id` FOREIGN KEY (`player_id`) REFERENCES `games_players` (`id`) ON DELETE CASCADE;

--
-- Contraintes pour la table `games_players`
--
ALTER TABLE `games_players`
  ADD CONSTRAINT `FK_team_id` FOREIGN KEY (`team_id`) REFERENCES `games_teams` (`id`) ON DELETE CASCADE,
  ADD CONSTRAINT `FK_user_id` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON DELETE CASCADE;

--
-- Contraintes pour la table `games_shots`
--
ALTER TABLE `games_shots`
  ADD CONSTRAINT `FK_shot_player_id` FOREIGN KEY (`player_id`) REFERENCES `games_players` (`id`) ON DELETE CASCADE;

--
-- Contraintes pour la table `games_teams`
--
ALTER TABLE `games_teams`
  ADD CONSTRAINT `FK_game_id` FOREIGN KEY (`game_id`) REFERENCES `games` (`id`) ON DELETE CASCADE;

--
-- Contraintes pour la table `players`
--
ALTER TABLE `players`
  ADD CONSTRAINT `FK_player_user_id` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`);

--
-- Contraintes pour la table `tokens`
--
ALTER TABLE `tokens`
  ADD CONSTRAINT `FK_tokens_user_id` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
