<?php
#Exo 1
#Q.0.01
require_once 'Connection.php';
$dsn = 'mysql:host=localhost;dbname=test;';
$user = "toto"; // A remplacer par vos identifiants
$password="toto"; // A remplacer par vos identifiants

try {
    $id=1;
    $nom='PERRET';
    $prenom='NINO';
    $nbAlbumsFaits=20;
    
	$con = new Connection($dsn, $user, $password);
    $query = "INSERT INTO tartiste VALUES('". $id ."', '". $nom ."', '". $prenom ."', '". $nbAlbumsFaits ."')";

    $con->executeQuery($query, array(
        ' :id' => array($id,PDO::PARAM_INT ),
        ' :nom' => array($nom,PDO::PARAM_STR),
        ' :prenom' => array($prenom,PDO::PARAM_STR),
        ' :nbAlbumsFaits' => array($nbAlbumsFaits,PDO::PARAM_INT)));

    echo "Insertion effectuée<br>";

    $query = "SELECT * FROM tartiste WHERE nom='PERRET' and prenom='NINO'";
    $stmt = $con->prepare($query);
    $stmt -> execute();
    $result = $stmt->fetchall();
    
	foreach ($result as $r) {
        echo "L'artiste ". $r['nom'] ." ".  $r['prenom'] ." a réalisé ". $r['nbAlbumsFaits'] ." albums<br />";
    }
} catch (PDOException $e){
    echo $e -> getMessage();
}