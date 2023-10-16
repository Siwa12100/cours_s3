<?php 

    include 'Connection/Connection.php';

    try {
        // $dsn = 'InnoDB:host=localhost;dbname=dbjemarcilla';
        $dsn = 'mysql:host=localhost;dbname=dbjemarcilla';
        $user = 'jemarcilla';
        $password = 'achanger';

        $db = new Connection($dsn, $user, $password);

    } catch(PDOException $e) {

        // traitement des exeptions liées à PDO...
    }

    function afficherLignesArticleAvecPDO(Connection $db) {
        $query = 'SELECT * FROM article';

        $stmt = $db -> prepare($query);

        $stmt -> execute();
        $results = $stmt -> fetchAll();

        foreach ($results as $row) {
            echo$row['id'];
            echo("<br><br>");
        }
    }

    function afficherLignesArticleAvecConnection(Connection $db) {
        if ($db -> executeQuery('SELECT * FROM article', []))
        echo("<br><br><br> --> Bonne exécution de la méthode executeQuerry de Connection ! <br><br>");
    
        foreach ($db -> getResults() as $ligne){
            echo $ligne['id'];
            echo("   |    ");
            echo $ligne['titre'];
            echo("   |    ");
            echo $ligne['texte'];
            echo("   |    ");
            echo $ligne['date'];

            echo("<br><br>");
        }
    }

    //afficherLignesArticle($db);
    afficherLignesArticleAvecConnection($db);

    function insertionArticle(int $id, string $titre, string $texte, Connection $db) {

        $requete = "INSERT INTO article ('id', 'titre', 'texte') VALUES ($id, '$titre', '$texte')";
        if ($db -> executeQuery($requete, []))
        echo("<br><br> --> Bonne exécution de l'insertion dans article ! <br>");
    }
    
    insertionArticle(118712, 'titre article fait depuis php', 'texte de article depuis php', $db);
?>