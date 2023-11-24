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
	
	echo "<a href=\"?page=0\" class=\"page-link\">Page 1</a>&nbsp";
	echo "<a href=\"?page=1\" class=\"page-link\">Page 2</a>&nbsp";
	echo "<a href=\"?page=2\" class=\"page-link\">Page 2</a>&nbsp";
	  
	echo "</body>
		</html>";