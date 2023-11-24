<?php
	class AdminControleur {
		function __construct() {
			global $rep, $vues, $action;
			$dVueErreur = array();

			try {		
				switch($action) {
					case NULL:
						echo "Pas d'action Admin";
						break;
					default:
						echo "Action Admin reçue : $action";
						break;
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