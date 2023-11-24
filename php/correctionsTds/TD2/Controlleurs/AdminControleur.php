<?php

// Chargement bibliothèques
require_once(__DIR__.'/Validation.php');


// Chargement config
include_once(__DIR__.'/../config/Config.php');

class AdminControleur {
	function __construct() {
		global $rep, $vues, $action, $con;
		$dataVueErreur = array();

		try {// On récupère l'action et on définit la fonction du constructeur à appeler
			if(isset($_REQUEST['action']) && !empty($_REQUEST['action'])) {
				$action = $_REQUEST['action'];
			}

			switch($action) {
				// Pas d'action, on réinitialise (1er appel lorsqu'un utilisateur arrive)
				case NULL:
					$this->Reinit();
					break;
					
				case "ajoutNews":
					$this->ajoutNews();
					break;

				// Mauvaise action, action non répertoriée
				default:
					$dataVueErreur[] =	"Erreur d'appel php";
					require($rep.$vues['erreur.php'];
					break;
			}

		} catch(PDOException $e) {
			// Gestion des exceptions pour les bases de données
			$dataVueErreur[] =	"Erreur PDO !!! ";
			require($rep.$vues['erreur.php'];

		} catch(Exception $e2) {
			// Gestion des exceptiox²ns autres
			$dataVueErreur[] =	"Erreur inattendue !!! ";
			require($rep.$vues['erreur.php'];
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
		
		
		require ($rep.$vues['vueBase.php'];
	}

	function ajoutNews() {
		$url=$_POST["url"];
		$nom=$_POST["nom"];
		Validation::val_form($url,$nom,$dataVueErreur);
		
		$newsGateway = new newsGateway();
		$data = $newsGateway->ajoutNews($con, $url, $nom);
		$dataVue = array(
			'url' => $url,
			'nom' => $nom,
			'data' => $data
		};
		
		require($rep.$vues['vueAjoutNews.php'];
	}
}