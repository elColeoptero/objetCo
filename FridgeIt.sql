-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Client :  localhost:3306
-- Généré le :  Dim 06 Juin 2021 à 19:48
-- Version du serveur :  5.7.27-0ubuntu0.19.04.1
-- Version de PHP :  7.2.24-0ubuntu0.19.04.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `FridgeIT`
--

-- --------------------------------------------------------

--
-- Structure de la table `t_cache`
--

CREATE TABLE `t_cache` (
  `codeBarre` bigint(11) NOT NULL
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
  `auteur` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `t_note`
--

INSERT INTO `t_note` (`id`, `date`, `message`, `auteur`) VALUES
(1, '2021-06-03', 'Ceci est un note ', 'Julien'),
(2, '2021-06-03', 'Ceci est une autre note', 'Samuel');

-- --------------------------------------------------------

--
-- Structure de la table `t_produit`
--

CREATE TABLE `t_produit` (
  `id` int(11) NOT NULL,
  `nom` text NOT NULL,
  `quantite` int(11) DEFAULT NULL,
  `peremption` date NOT NULL,
  `codeBarre` bigint(11) NOT NULL,
  `marque` text,
  `outside` tinyint(1) NOT NULL,
  `en_nom` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Table contenant les informations sur les produits scannés ';

--
-- Contenu de la table `t_produit`
--

INSERT INTO `t_produit` (`id`, `nom`, `quantite`, `peremption`, `codeBarre`, `marque`, `outside`, `en_nom`) VALUES
(4, 'Poudre', 100, '2008-07-04', 1, 'Nutella', 0, ''),
(15, 'Panzani spaghetti plat', 500, '2021-05-05', 3038350208613, 'Panzani', 0, ''),
(29, 'Barre moelleuse chocolat noir et noisettes', 0, '2021-05-05', 7622210547194, 'Not found', 0, '');

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
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT pour la table `t_produit`
--
ALTER TABLE `t_produit`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=38;
--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `t_historique`
--
ALTER TABLE `t_historique`
  ADD CONSTRAINT `FK_idProduit` FOREIGN KEY (`idProduit`) REFERENCES `t_produit` (`id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
