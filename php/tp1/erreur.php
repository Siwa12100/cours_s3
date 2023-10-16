<html>
    <body>
        <h1>Scripts PHP</h1>
        <h2>Q.1</h2>
            <?php
                foreach ($TMessage as $erreur){
                    echo " - $erreur".'</br>';
                }
            ?>
        </br>
        <h2>Q.2</h2> 
        Test pourcentage avis (f, 30, 70) :
        <?php 
            $val = pourcentageAvis('f', 30, 70);
            if ($val != -1){
                echo $val.'</br>';
            }
            else
            {
                echo "erreur dans le passage de paramètres".'</br>';
            }
        ?> 

        Test pourcentage avis (d, 0, 100) :
        <?php 
            $val = pourcentageAvis('d', 0, 100);
            if ($val != -1){
                echo $val.'</br>';
            }
            else
            {
                echo "erreur dans le passage de paramètres".'</br>';
            }
        ?>

        <h2>Q.3</h2>

        Test pourcentage avis (d, 0, 0) :
            <?php 
                    try{

                        pourcentageAvis("d", 0, 0);
                    }
                    catch(Exception $e){
                            echo $e->getMessage();        
                    }
            ?>
        </body>
</html>






