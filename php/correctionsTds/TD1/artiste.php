<?php
require_once("ArtisteGateway.php");

Class Artiste {
	protected $id;
	protected $nom;
	protected $prenom;
	protected $nbAlbumsFaits;
	
	function __construct(int $i, string $n,string $p, int $nb) {
		$this->id=$i;
		$this->nom=$n;
		$this->prenom=$p;
		$this->nbAlbumsFaits=$nb;
	}

	function get_id() : int {
		return $this->id;
	}

	function get_nom(): string {
		return $this->nom;
	}
	function get_prenom(): string {
		return $this->prenom;
	}
	function get_nbAlbumsFaits(): int {
		return $this->nbAlbumsFaits;
	}
	
	function get_byName(): array {
		$AG = new ArtisteGateway();
		$tabArtistes = FindByName($this->nom);
		return $tabArtistes;
	}
}