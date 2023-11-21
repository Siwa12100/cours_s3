<?php

use modele\ArticleManager;

echo "coucouuuu V2 ! ";

$manager = new ArticleManager();
$articleCourant = $manager -> getArticle(8);


echo "fin de l'index.php...";
?>