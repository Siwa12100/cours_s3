<?php
    namespace modele;

    abstract class Contenu {
        private int $id;
        private $typeContenu;

        public function __construct(int $id) {
            $this -> id = $id;
        }
        
        public function  getId() : int {
            return $this -> id;
        }

        public function getTypeContenu() : string {
            return $this -> typeContenu;
        }

        protected function setTypeContenu(string $type) {
            $this -> typeContenu = $type;
        }
    }

?>