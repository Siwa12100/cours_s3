<?php	
	echo "<!doctype html>";
	echo "<html lang=\"fr\">";
	echo "<head>
			<meta charset=\"utf-8\">
			<title>Titre de la page</title>
		</head>";
	echo "<body>";
	
	foreach($news as $row) {
			echo "<p>". $row->get_url() ." // ". $row->get_nom() ."</p>";
	}

	for($i = 1; $i <= $nbNewsEnBase; $i++) {
		echo "<a href=\"?page=$i\" class=\"page-link\">Page $i</a>&nbsp";
	}
	echo "</body>
		</html>";