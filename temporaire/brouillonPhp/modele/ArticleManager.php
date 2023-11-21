<?php

namespace modele;

use Metier\Article;

    class ArticleManager {

        private $dataManager;
        private $articletheque;

        public function __construct() {
            $this -> dataManager = new stubArticles();
            $this -> articletheque = new Articletheque($this -> dataManager);
        }

        public function getArticle(int $id) : Article {

            return $this -> articletheque -> getArticle($id);
        }
    }
?>