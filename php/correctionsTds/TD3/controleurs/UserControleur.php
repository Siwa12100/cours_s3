<?php
	class UserControleur {
		function __construct() {
			global $rep, $vues, $action;
			$dVueErreur = array();

			try {				
				switch($action) {
					case NULL:
						echo "Pas d'action User";
						break;
					default:
						echo "Action User reçue : $action";
						break;
				}
			} catch(PDOException $e) {
				$dVueErreur[] =	"Erreur base de données !";
				require ($rep.$vues['erreur']);
			} catch(Exception $e) {
				$dVueErreur[] =	"Erreur générale !";
				require ($rep.$vues['erreur']);
			}
		}
	}