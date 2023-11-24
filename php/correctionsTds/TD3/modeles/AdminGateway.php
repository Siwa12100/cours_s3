<?php
	class AdminGateway {
		private $con;
		private $query;
		private $results;

		public function __construct(Connection $con) {
			$this->con = $con;
		}


		public function getLogin($login) {
			$query="SELECT login FROM users WHERE login=:login";
			$this->con->executeQuery($query,array(
				':login' => array($login, PDO::PARAM_STR)
			));
			
			$results=$this->con->getResults();
			return $results;
		}
		
		public function getPassword($login) {
			$query="SELECT password FROM users WHERE login=:login";
			$this->con->executeQuery($query,array(
				':login' => array($login, PDO::PARAM_STR)
			));
			
			$results=$this->con->getResults();
			return $results;
		}
	}
