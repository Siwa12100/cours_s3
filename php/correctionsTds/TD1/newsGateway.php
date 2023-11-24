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
	}
	