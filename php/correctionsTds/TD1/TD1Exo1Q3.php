<?php
	// Solutions HONTEUSEMENT récupérées sur le site
	// https://welovedevs.com/fr/articles/astucedecode-9-les-constructeurs-en-php/
	// Elles sont écrites par Adrien MOTTE, merci à lui de ne pas m'obliger à écrire ce genre de choses que je ne recommande pas du tout
	// PS : ses explications sont très bonnes
	
	// Solution 1 : switch dans le constructeur sur le nombre d'arguments par exemple
	class Artiste {
		public $constructArtiste;

		function __construct()
		{
			switch(func_num_args())
			{
				case 1:
					$this->constructArtiste = func_get_arg(0);
					break;
				case 2:
					$this->constructArtiste = func_get_arg(0) + func_get_arg(1);
					break;
			}
			// Trucs à initialiser communs aux deux constructions
		}
	}

	// Initialisation
	$a = new Artiste(42); // Artiste = 42
	$b = new Artiste(20, 15); // Artiste = 35
	
	// Solution 2 : un constructeur "classique" suivi de fonctions statiques à appeller pour vos besoins
	class Artiste {
		public $constructArtiste;

		function __construct() {
			// Trucs à initialiser communs aux deux constructions
		}

		static public function __construct_with_one_arg($arg) {
			$instance = new static();
			$instance->constructArtiste = $arg;
			return $instance;
		}

		static public function __construct_with_two_args($arg1, $arg2) {
			$instance = new static();
			$instance->constructArtiste = $arg1 + $arg2;
			return $instance;
		}
	}

	//Initialisation
	$a = Artiste::__construct_with_one_arg(42); // constructArtiste = 42
	$b = Artiste::__construct_with_two_args(20, 15); // constructArtiste = 35