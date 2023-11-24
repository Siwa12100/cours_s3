<?php
	class MdlAdmin {
		function __construct() {
			global $con;
			$this->ag = new AdminGateway($con);
		}

		function connexion() {
			$login=$_POST['login'];
			$password=$_POST['password'];
			$login=Nettoyer::nettoyer_string($login);
			$role=Nettoyer::nettoyer_string($role);
			
			$loginFromDataBase = $this->ag->getLogin($login);
			$passwordFromDataBase = $this->ag->getPassword($login);
			
			if(password_verify($password, $passwordFromDatabase)) {
				$_SESSION['role'] = "admin";
				$_SESSION['login'] = $login;
			} else {
				$dVueErreur[] = "Login ou mot de passe incorrect";
				throw new Exception("Login ou mot de passe incorrect", 1);
			}
		}

		function deconnexion() {
			$_SESSION = array();
			session_unset();
			session_destroy();			
		}
		
		function isAdmin() {
			if(isset($_SESSION['login']) && isset($_SESSION['role'])) {
				$login=Nettoyer::nettoyer_string($_SESSION['login']);
				$role=Nettoyer::nettoyer_string($_SESSION['role']);
				
				//return new Admin($login, $role);
				return true;
			} else {
				return NULL;
			}
		}
	}