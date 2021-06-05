-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Client :  localhost:3306
-- Généré le :  Jeu 03 Juin 2021 à 12:45
-- Version du serveur :  10.3.27-MariaDB-0+deb10u1
-- Version de PHP :  7.3.27-1~deb10u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `FridgeIt`
--

-- --------------------------------------------------------

--
-- Structure de la table `t_cache`
--

CREATE TABLE `t_cache` (
  `codeBarre` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Table contenant les informations des produits deja telecharg';

--
-- Contenu de la table `t_cache`
--

INSERT INTO `t_cache` (`codeBarre`) VALUES
(1);

-- --------------------------------------------------------

--
-- Structure de la table `t_historique`
--

CREATE TABLE `t_historique` (
  `id` int(11) NOT NULL,
  `date` date NOT NULL,
  `quantitie` int(11) NOT NULL,
  `action` text NOT NULL,
  `idProduit` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Structure de la table `t_note`
--

CREATE TABLE `t_note` (
  `id` int(11) NOT NULL,
  `date` date NOT NULL,
  `message` text NOT NULL,
  `auteur` text DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Structure de la table `t_produit`
--

CREATE TABLE `t_produit` (
  `id` int(11) NOT NULL,
  `nom` text NOT NULL,
  `quantite` int(11) DEFAULT NULL,
  `peremption` date NOT NULL,
  `codeBarre` int(11) NOT NULL,
  `marque` text DEFAULT NULL,
  `outside` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Table contenant les informations sur les produits scannés ';

--
-- Contenu de la table `t_produit`
--

INSERT INTO `t_produit` (`id`, `nom`, `quantite`, `peremption`, `codeBarre`, `marque`, `outside`) VALUES
(4, 'Poudre', 100, '2008-07-04', 1, 'Nutella', 0),
(5, 'Poudre', 100, '2008-07-04', 1, 'Nutella', 0),
(6, 'Poudre', 100, '2008-07-04', 1, 'Nutella', 0),
(7, 'Poudre', 100, '2008-07-04', 1, 'Nutella', 0),
(8, 'Poudre', 100, '2008-07-04', 1, 'Nutella', 0),
(9, 'Poudre', 100, '2008-07-04', 1, 'Nutella', 0);

--
-- Index pour les tables exportées
--

--
-- Index pour la table `t_cache`
--
ALTER TABLE `t_cache`
  ADD PRIMARY KEY (`codeBarre`);

--
-- Index pour la table `t_historique`
--
ALTER TABLE `t_historique`
  ADD KEY `FK_idProduit` (`idProduit`);

--
-- Index pour la table `t_note`
--
ALTER TABLE `t_note`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `t_produit`
--
ALTER TABLE `t_produit`
  ADD PRIMARY KEY (`id`),
  ADD KEY `FK_codeBarre` (`codeBarre`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `t_note`
--
ALTER TABLE `t_note`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT pour la table `t_produit`
--
ALTER TABLE `t_produit`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;
--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `t_historique`
--
ALTER TABLE `t_historique`
  ADD CONSTRAINT `FK_idProduit` FOREIGN KEY (`idProduit`) REFERENCES `t_produit` (`id`);

--
-- Contraintes pour la table `t_produit`
--
ALTER TABLE `t_produit`
  ADD CONSTRAINT `FK_codeBarre` FOREIGN KEY (`codeBarre`) REFERENCES `t_cache` (`codeBarre`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
