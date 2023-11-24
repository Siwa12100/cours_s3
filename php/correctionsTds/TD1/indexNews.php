<?php
	require_once 'config.php';
	require_once 'newsGateway.php';
	
	$newsGateway = new NewsGateway($con);
	$news = $newsGateway->FindByPage($page, $offset);

	require_once 'TD1EXo2Q5.php';