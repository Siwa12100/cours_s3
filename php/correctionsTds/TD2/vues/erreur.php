<!DOCTYPE HTML>

<html>
<head><title>Erreur</title>
</head>

<body>

<h1>ERREUR !!!!!</h1>
<?php
if (isset($dataVueEreur)) {
	foreach ($dataVueEreur as $value){
		echo $value;
	}
}
?>

</body>
</html> 