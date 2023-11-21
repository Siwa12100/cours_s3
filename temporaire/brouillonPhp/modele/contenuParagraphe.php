<?php 

    namespace modele;

    class contenuParagraphe extends Contenu {

        private $titre;
        private $texte;

        public function __construct(int $id, string $titre, string $texte) {
            parent::__construct($id);
            $this -> titre = $titre; 
            $this -> texte = $texte;

            $this -> setTypeContenu("paragraphe");
        }

        public function getTitre() : String {
            return $this -> titre;
        }

        public function getTexte() : String {
            return $this -> texte;
        }

        public function setContenu(String $texte) {
            $this -> texte = $texte;
        }

        public function setTitre(String $titre) {
            $this -> titre = $titre;
        }

        public function getContenu() : array {
            $temp = array();
            $temp['titre'] = $this -> titre;
            $temp['contenu'] = $this -> texte;
            
            return $temp;
        }
    }

?>