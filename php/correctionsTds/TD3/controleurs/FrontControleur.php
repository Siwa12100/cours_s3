<?php
	class FrontControleur {
		function __construct() {
			global $rep, $vues, $action;
			$listeAction_Admin = array('connecter', 'deconnecter', 'ajouter', 'supprimer');

			$dVueErreur = array();

			try {
				$isAdmin = new MdlAdmin();

				if(isset($_REQUEST['action']) && !empty($_REQUEST['action'])) {
					$action = $_REQUEST['action'];
				}
				
				if(in_array($action, $listeAction_Admin)) {
					if($isAdmin->isAdmin() == NULL) {
						require ($rep.$vues['vueBase']);
					} else {
						$admin = new AdminControleur();
					}
				} else {
					$user = new UserControleur();
				}
			}
			catch(PDOException $e) {
				$dVueErreur[] =	"Erreur base de données !";
				require ($rep.$vues['erreur']);
			}
			catch(Exception $e) {
				$dVueErreur[] =	"Erreur générale !";
				require ($rep.$vues['erreur']);
			}
		}
	}