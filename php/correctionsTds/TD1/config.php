<?php
	// Connexion BDD
	require_once 'Connection.php';

	$dsn = 'mysql:host=localhost;dbname=test;';
	$user = "toto"; // A remplacer par vos identifiants
	$password="toto"; // A remplacer par vos identifiants

	try {		
		$con = new Connection($dsn, $user, $password);
	} catch (PDOException $e){
		echo $e -> getMessage();
	}	
	
	// Pagination
	$page = 0;
	$offset = 2;
	
	if(isset($_GET["page"]) && !empty($_GET["page"])) {
		$page = $_GET["page"];
	}