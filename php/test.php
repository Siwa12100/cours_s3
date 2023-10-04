<?php

    $TMessage = array ("Division par zéro", "Valeur invalide");
    require("erreur.php");

    function pourcentageAvis(string $typeAvis, int $nbAvisFav, int $nbAvisDeFav) : int {
        $total = $nbAvisDeFav + $nbAvisFav;
        //if ($total <= 0) return -1;
        if ($total <= 0) throw new Exception("[Erreur] : division par 0 ! ");

        if ($typeAvis == 'favorable' || $typeAvis == 'f' ){
            return ($nbAvisFav / $total ) * 100;
        }

        if ($typeAvis == 'defavorable' || $typeAvis == 'd'){
            
            return ($nbAvisDeFav / $total) * 100;
        }
        
        // Cas où le type passé en paramètre ne correspond pas bien 
        return -1;
    }




    



    //echo "fin du bloc php de test.php";
?>