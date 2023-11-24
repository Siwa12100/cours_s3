<?php

// Chargement bibliothèques
require_once(__DIR__.'/Validation.php');
require_once(__DIR__.'/../modeles/Simplemodel.php');

// Chargement config
include_once(__DIR__.'/../config/Config.php');

class UserControleur {
	function __construct() {
		global $rep, $vues, $action, $con;
		$dataVueErreur = array();

		try {// On récupère l'action et on définit la fonction du constructeur à appeller
			$action=$_REQUEST['action'];

			switch($action) {
				// Pas d'action, on réinitialise (1er appel lorsqu'un utilisateur arrive)
				case NULL:
					Reinit();
					break;
					
				case "listeNews":
					listeNews();
					break;

				case "newsFavorites":
					newsFavorite();
					break;

				// Mauvaise action, action non répertoriée
				default:
					$dataVueErreur[] =	"Erreur d'appel php";
					require($rep.'/../vues/erreur.php');
					break;
			}

		} catch (PDOException $e) {
			// Gestion des exceptions pour les bases de données
			$dataVueErreur[] =	"Erreur PDO !!! ";
			require ($rep.'/../vues/erreur.php');

		} catch (Exception $e2) {
			// Gestion des exceptiox²ns autres
			$dataVueErreur[] =	"Erreur inattendue !!! ";
			require ($rep.'/../vues/erreur.php');
		}
	}

	// Fonctions du contrôleur
	// Chaque action définie au dessus => une fonction ci-dessous
	// 
	function Reinit() {
		$dataVue = array();
		$model = new \modeles\listeNews();
		$data=$model->get_Liste();

		$dVue = array (
			'nom' => $nom,
			'url' => $url,
			'data' => $data,
			);
		require (__DIR__.'/../vues/vueBase.php');
	}

	function ajoutNews() {
		$news = new news();
		$dataVue = $news->favori($url, $nom);
		require ($rep.'/../vues/vueAjoutNews.php');
	}
	
	function listeNews() {
		$dataVue = array();
		$model = new \modeles\listeNews();
		$data=$model->get_Liste();

		$dVue = array (
			'nom' => $nom,
			'url' => $url,
			'data' => $data,
			);
		require (__DIR__.'/../vues/vueBase.php');
	}

	function newsFavorites() {
		$news = new news();
		$dataVue = $news->newsFavorites();
		require ($rep.'/../vues/vueBase.php');
	}
}