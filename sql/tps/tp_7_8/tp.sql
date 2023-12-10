
-- Q.1)
------

-- Elle sélectionne le rôle et le catalogue courant...


-- Q.2)
------

-- Drop Table Log;
-- CREATE TABLE Log (
--     quand timestamp,
--     qui char(20),
--     quoi varchar(800),
--     action varchar(50),
--     PRIMARY KEY(quand, qui, quoi, action)
-- );


-- Q.3)
------

-- INSERT INTO Player Values (1001, 'Todd Jackson', 'USA');
-- INSERT INTO Player Values (1002, 'Michael Matthews', 'USA');
-- INSERT INTO Player Values (1003, 'Jamie Griffith', 'USA');
-- INSERT INTO Player Values (1004, 'Iloy Roberts', 'Belgium');
-- INSERT INTO Player Values (1005, 'Erin Kolthof', 'Belgium');


-- Q.4)
------

-- Create Or Replace Function traceSuppression() Returns trigger AS $$
-- DECLARE
--     infos varchar(200);
-- BEGIN
--     infos = 'Joueur ' || OLD.name || '(' || OLD.id || ')' || 'supprime';
--     Insert Into Log Values (CURRENT_TIMESTAMP, current_role, infos, 'suppression');
--     RETURN OLD;
-- END;
-- $$ LANGUAGE plpgsql;

-- Drop trigger if EXISTS traceOnDelete On Player;
-- Create trigger traceOnDelete AFTER DELETE ON Player
-- For Each Row
-- Execute Function traceSuppression();

-- Q.5)
------

-- DELETE From Player
-- WHERE name = 'Michael Matthews';

-- DELETE From Player
-- Where country = 'Belgium';

-- SELECT * FROM Log;


-- Q.6)
------

Create Or Replace Function tracePlayer() Returns trigger AS $$
DECLARE
    infos varchar(200);
BEGIN
    IF TG_OP = 'DELETE' THEN 
        infos = 'Joueur ' || OLD.name || '(' || OLD.id || ')' || 'supprime';
        Insert Into Log Values (CURRENT_TIMESTAMP, current_role, infos, 'suppression');
        RETURN OLD;
    END IF;

    IF TG_OP = 'UPDATE' THEN
        infos = 'Joueur ' || NEW.name || '(' || NEW.id || ')' || 'modifie';
        -- RAISE NOTICE '[Temporaire infos] : %', infos;
        Insert Into Log Values (CURRENT_TIMESTAMP, current_role, infos, 'modification');
        RETURN NEW;
    END IF;

    IF TG_OP = 'INSERT' THEN
        infos = 'Joueur ' || NEW.name || '(' || NEW.id || ')' || 'rajoute';
        -- RAISE NOTICE '[Temporaire infos] : %', infos;
        Insert Into Log Values (CURRENT_TIMESTAMP, current_role, infos, 'insertion');
        RETURN OLD;
    END IF;
END;
$$ LANGUAGE plpgsql;

Drop trigger if EXISTS traceOnInsert On Player;
Create trigger traceOnInsert AFTER INSERT ON Player
For Each Row
Execute Function tracePlayer();

Drop trigger if EXISTS traceOnUpdate On Player;
Create trigger traceOnUpdate AFTER UPDATE ON Player
For Each Row
Execute Function tracePlayer();

Drop trigger if EXISTS traceOnDelete On Player;
Create trigger traceOnDelete AFTER DELETE ON Player
For Each Row
Execute Function tracePlayer();

-- INSERT INTO Player VALUES (2000, 'Louise', 'Aveyron');

-- UPDATE Player 
-- SET country = 'France'
-- WHERE id = '2000';

-- DELETE FROM Player 
-- WHERE id = '2000';


-- Q.7) 
------

-- SELECT * from Log;

--            quand            |         qui          |               quoi                |    action    
-- ----------------------------+----------------------+-----------------------------------+--------------
--  2023-12-06 08:49:39.566799 | jemarcilla           | dbjemarcilla                      | suppression
--  2023-12-06 09:01:09.45039  | jemarcilla           | Joueur Iloy Roberts(1004)supprime | suppression
--  2023-12-06 09:01:09.45039  | jemarcilla           | Joueur Erin Kolthof(1005)supprime | suppression
--  2023-12-06 09:23:32.376194 | jemarcilla           | Joueur Louise(2000)rajoute        | insertion
--  2023-12-06 09:23:32.378125 | jemarcilla           | Joueur Louise(2000)modifie        | modification
--  2023-12-06 09:24:18.960142 | jemarcilla           | Joueur Louise(2000)modifie        | modification
--  2023-12-06 09:24:18.961971 | jemarcilla           | Joueur Louise(2000)supprime       | suppression
--  2023-12-06 09:24:39.923599 | jemarcilla           | Joueur Louise(2000)rajoute        | insertion
--  2023-12-06 09:24:39.925161 | jemarcilla           | Joueur Louise(2000)modifie        | modification
--  2023-12-06 09:24:39.926763 | jemarcilla           | Joueur Louise(2000)supprime       | suppression
--  2023-12-06 09:25:49.591845 | jemarcilla           | Joueur Louise(2000)rajoute        | insertion
--  2023-12-06 09:25:49.593613 | jemarcilla           | Joueur Louise(2000)modifie        | modification
--  2023-12-06 09:25:49.595058 | jemarcilla           | Joueur Louise(2000)supprime       | suppression


-- Q.8)
------

Create table if not exists BestScorer(

    points numeric,
    idPlayer varchar(10) REFERENCES Player(id),
    idMatch char(8) REFERENCES Game(id),
    PRIMARY KEY (idPlayer, idMatch)
);


-- Q.9)
------

-- Pour info, on part de la table Gamedetail pour le trigger...


-- Create Or Replace Function traceBestScorer() Returns trigger AS $$
-- DECLARE
--     infos varchar(200);
-- BEGIN
--     infos = 'Joueur ' || NEW.idPlayer || '( match : ' || NEW.idGame || ' et Score : ' || NEW.points || ')' || 'rajoute a BestScorer';
--     RAISE NOTICE '[Temporaire infos] : %', infos;
--     Insert Into Log Values (CURRENT_TIMESTAMP, current_role, infos, 'insertion');
--     RETURN OLD;    

-- END;
-- $$ LANGUAGE plpgsql;

Create Or Replace Function traceBestScorer() Returns trigger AS $$
DECLARE
    infos varchar(200);
BEGIN
    

    RETURN OLD;    

END;
$$ LANGUAGE plpgsql;

SELECT * from Log;

