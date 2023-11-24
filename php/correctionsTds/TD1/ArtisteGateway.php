<?php
require_once("Artiste.php");

class ArtisteGateway extends Artiste {
    private $con;

    function __construct(Connection $con){
        $this->con= $con;
    }

    function FindByName(string $nom): array{
        $query = "SELECT * FROM tartiste WHERE nom='$nom'";
        $stmt = $this->con->prepare($query);
        $stmt->execute();
		
        $result = $stmt->fetchAll();

		$artistes = array();
        foreach ($result as $row){
            $a = new Artiste($row['id'], $row['nom'], $row['prenom'], $row['nbAlbumsFaits']);
            array_push($artistes, $a);
			// Autre solution : $artistes[] = $a; Dans ce cas, la déclaration préalable de $artistes n'est plus nécessaire
        }

        return $artistes;
    }
}