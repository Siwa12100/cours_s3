<?php
try{
    require_once 'ArtisteGateway.php';
    require_once 'Connection.php';
	
    $user = "toto";
    $password = "toto";
    $dsn = 'mysql:host=localhost;dbname=test';

    $con = new Connection($dsn, $user, $password);
    $AG = new ArtisteGateway($con);
    $tab = $AG->FindByName("PERRET");
	
    foreach($tab as $row){
        echo $row->get_id()."<br>";
        echo $row->get_nom()."<br>";
        echo $row->get_prenom()."<br>";
        echo $row->get_nbAlbumsFaits()."<br>";
    }
} catch(Exception $e){
    echo $e->getMessage();
}
