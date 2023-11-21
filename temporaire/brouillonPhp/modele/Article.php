<?php

    namespace metier;

    use modele;

    class Article {
        private $id;
        private $titre;
        private $description;
        private $temps;
        private $date;
        
        private $lContenus;

        public function __construct( $id, $title, $content, $temps, $date) {
            $this->id = $id;
            $this->titre = $title;
            $this->description = $content;
            $this->temps = $temps;
            $this->date = $date;
            $this -> lContenus = array();
        }

        public function remplirArticle($lContenus) {
            foreach ($lContenus as $contenu) {
                $this -> lContenus[] = $contenu; 
            }
        }

        public function getId() {
            return $this->id;
        }

        public function getTitle() {
            return $this->titre;
        }

        public function getDescription() {
            return $this->description;
        }

        public function getTemps() {
            return $this->temps;
        }

        public function getDate() {
            return $this->date;
        }

        private function setId( $id ) {
            $this->id = $id;
        }

        private function setTitle( $title ) {
            $this->titre = $title;
        }

        private function setDescription( $content ) {
            $this->description = $content;
        }

        private function setTemps( $temps ) {
            $this->temps = $temps;
        }

        private function setDate( $date ) {
            $this->date = $date;
        }
    }

?>