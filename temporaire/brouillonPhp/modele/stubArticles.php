<?php

namespace modele;

use Modele\manager\IArticleDataManager;
use Metier\Article;

    class stubArticles implements IArticleDataManager {

        private $lArticles;

        public function __construct() {
            $this -> chargerArticles();
        }        

        public function chargerArticles() {
            
            $temp = array();
            $temp[] = new Article(1, "Titre du premier Article", "Contenu du premier article...\n seconde ligne...", 3, date("d-m-Y"));
            $temp[] = new Article(2, "Titre du second Article", "Contenu du second article...\n seconde ligne...", 20, date("d-m-Y"));
            $temp[] = new Article(3, "Titre du troisième Article", "Contenu du troisième article...\n seconde ligne... \n troisième ligne ", 7, date("d-m-Y"));
            $temp[] = new Article(4, "Titre du quatrième Article", "Contenu du quatrième article...\n\n\n seconde ligne...", 100, date("d-m-Y"));
            
            foreach($temp as $article) {
                $article -> remplirArticle($this -> chargerContenuParagraphe());
            }

            $this -> lArticles = $temp;
        }

        public function chargerContenuParagraphe() : array {

            $temp = array();

            $temp[] = new contenuParagraphe(1, "Premier paragraphe", "Contenu du premier article et tout et tout....");
            $temp[] = new contenuParagraphe(2, "Titre du second paragraphe", "Contenu du second paragraphe....");
            return $temp;
        }

        public function getArticle(int $id) : Article {
            return $this -> lArticles[0]; 
        }

        public function getAllArticles() : array {
            return $this -> lArticles;
        }

    }

?>