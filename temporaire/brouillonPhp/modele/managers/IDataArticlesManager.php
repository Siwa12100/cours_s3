<?php

    namespace modele\manager;

    interface IArticleDataManager {

        public function getAllArticles();
        public function getArticle(int $id);
    }

?>