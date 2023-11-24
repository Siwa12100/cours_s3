<?php
	require 'news.php';

	class NewsGateway extends News {
		private $con;

		function __construct(Connection $con){
			$this->con= $con;
		}

		function FindByPage(int $page, int $offset) {
			$limit = $page * $offset;
			$query = "SELECT * FROM tnews LIMIT $limit, $offset";

			$stmt = $this->con->prepare($query);
			$stmt->execute();

			$results = $stmt->fetchAll();
			foreach ($results as $row){
				$new = new news($row['URL'], $row['nom']);
				$news[] = $new;
			}

			return $news;
		}
		
		function ajoutNews($con, string $url, string $nom) {
			$query = "INSERT INTO news VALUE (':url', ':nom')";
			
			$con->executeQuery($query, array(
					':url' => array($url, PDO::PARAM_STR),
					':nom' => array($nom, PDO::PARAM_STR)
			));
			
			return TRUE;
		}
	}
	