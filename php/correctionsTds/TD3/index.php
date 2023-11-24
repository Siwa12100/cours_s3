<?php

// Si controleur pas objet
// header('Location: controller/controller.php');

// Si controleur objet

// Chargement config
require_once(__DIR__.'/config/config.php');

// Chargement autoloader pour autochargement des classes
require_once(__DIR__.'/config/Autoload.php');
Autoload::charger();
session_start();
			
$con = new Connection($dsn,$login,$passwd);
$cont = new FrontControleur();