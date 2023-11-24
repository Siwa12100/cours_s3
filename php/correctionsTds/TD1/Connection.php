<?php
	class Connection extends PDO{
		private $stmt;
		private $user;
		private $password;
		private $dsn;

		function __construct($d, $u, $p){
			parent::__construct($d, $u, $p);
			$this->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		}

		function executeQuery(string $query, array $parameter=[]) :bool{
			$this->stmt =parent::prepare($query);
			foreach($parameter as $name => $value){
				$this->stmt->bindValue($name, $value[0], $value[1]);
			}
			return $this->stmt->execute();
		}
	}