-- TP 3 - SQL
-- ===========


-- Partie 1 - Concurrence
-- ======================

-- Question 5  : 
----------------
/* 
    La première requête de U1 va récupérer l'ensemble des games après le 2022-01-01. 

    La requête de U2 va supprimer une partie des games de la table. 

    U1 voit toujours les lignes suppimées car le U2 n'a pas commit. 

    Après le commit de U2, en effet, U1 ne voit plus les parties après le 2022-01-01....
*/



-- Question 6 : 
---------------
/*
    Après que le U1 ait fait le premier delete (sans commit), le U2 se retrouve à avoir sa commande en attente
    (tourne dans le vide), jusqu'à ce que U1 fasse son rollback...

    On fait des rollback pour annuler nos modifications...
*/


-- Question 7 : 
---------------
/* 
    U2 commence par mettre à jour la table, sans soucis... 

    U1 est mit en attente lorsqu'il rentre son Alter table...

    Une fois que U2 rollback, L'alter table de U1 se termine enfin. 
*/



-- Question 8 : 
---------------

    -- U2 :
        -- DELETE FROM Tp3
        -- WHERE id='10300002';

        -- Le delete s'est bien passé....

        -- DELETE FROM Tp3
        -- WHERE id='10300001';

        -- Le delete est mis en attente car U1 a mis un verrou sur la ligne en question...

        -- Vu que U2 fait ensuite une commande qui créée une action d'interblocage, toute sa 
        -- transaction est annulée est ce que U1 faisait est bien validé..

        


