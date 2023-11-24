<?php
	Class News {
		protected $url;
		protected $nom;
		
		function __construct(string $u, string $n) {
			$this->url=$u;
			$this->nom=$n;
		}

		function get_url() : string {
			return $this->url;
		}

		function get_nom(): string {
			return $this->nom;
		}
	}