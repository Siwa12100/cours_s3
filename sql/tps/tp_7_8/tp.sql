
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

--DROP TABLE BestScorer;
Create table if not exists BestScorer(

    points numeric,
    idPlayer varchar(10) REFERENCES Player(id),
    idGame char(8) REFERENCES Game(id),
    PRIMARY KEY (idGame)
);


-- Q.9)
------

Create Or Replace Function traceBestScorer() Returns trigger AS $$
DECLARE

    ptsActuels numeric;
    ptsMax numeric;
    matchsCourant char(8);
    nbLignes numeric;

BEGIN

    ptsActuels = NEW.points;
    matchsCourant = NEW.idGame;
    
    SELECT INTO nbLignes COUNT(*)
    FROM BestScorer
    WHERE idGame = NEW.idGame;

    IF nbLignes = 0 THEN
        ptsMax = 0;
    
    ELSE
        SELECT bt.points INTO STRICT ptsMax
        FROM BestScorer bt
        WHERE bt.idGame = matchsCourant;

    END IF;  

    IF ptsActuels > ptsMax THEN
        IF nbLignes = 0 THEN
            INSERT INTO BestScorer VALUES(ptsActuels, NEW.idPlayer, matchsCourant);
        ELSE
            UPDATE BestScorer 
            SET points = ptsActuels,
            idPlayer = NEW.idPlayer
            WHERE idGame = NEW.idGame;
        END IF;
    END IF;

    RETURN NEW;

END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS triggerBestScorer ON Gamedetail;
CREATE TRIGGER triggerBestScorer BEFORE INSERT ON Gamedetail
FOR EACH ROW
EXECUTE FUNCTION traceBestScorer();

-- SELECT * from Log;

-- 10.)
------

DELETE FROM GameDetail
WHERE idGame = '22101005';

INSERT INTO GameDetail VALUES('22101005','1610612750','1630162','F',NULL,'0 0:36:22',4,10,0.4,3,8,0.375,4,4,1,0,8,8,5,3,1,1,1,15,5);
INSERT INTO GameDetail VALUES('22101005','1610612750','1630183','F',NULL,'0 0:23:54',6,8,0.75,1,3,0.333,1,1,1,2,4,6,0,0,2,2,6,14,10);
INSERT INTO GameDetail VALUES('22101005','1610612750','1626157','C',NULL,'0 0:25:17',4,9,0.444,1,3,0.333,6,8,0.75,1,9,10,0,0,0,3,4,15,14);
INSERT INTO GameDetail VALUES('22101005','1610612750','1627736','G',NULL,'0 0:30:52',4,9,0.444,4,9,0.444,0,0,0,0,3,3,1,1,0,1,4,12,20);
INSERT INTO GameDetail VALUES('22101005','1610612750','1626156','G',NULL,'0 0:33:46',3,13,0.231,1,6,0.167,7,7,1,0,6,6,9,1,0,5,0,14,17);
INSERT INTO GameDetail VALUES('22101005','1610612750','1629675',NULL,NULL,'0 0:23:56',3,8,0.375,1,2,0.5,4,4,1,3,7,10,1,3,2,1,1,11,-7);
INSERT INTO GameDetail VALUES('22101005','1610612750','1629162',NULL,NULL,'0 0:21:00',2,5,0.4,0,1,0,1,1,1,0,1,1,3,3,0,0,1,5,-10);
INSERT INTO GameDetail VALUES('22101005','1610612750','1629669',NULL,NULL,'0 0:21:35',6,13,0.462,2,5,0.4,2,2,1,0,0,0,1,0,0,0,0,16,-5);
INSERT INTO GameDetail VALUES('22101005','1610612750','1627752',NULL,NULL,'0 0:22:53',3,8,0.375,2,5,0.4,3,5,0.6,0,2,2,1,1,0,1,2,11,1);
INSERT INTO GameDetail VALUES('22101005','1610612750','1629006',NULL,NULL,'0 0:0:25',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
INSERT INTO GameDetail VALUES('22101005','1610612750','1630195',NULL,'DNP - Coach''s Decision',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO GameDetail VALUES('22101005','1610612750','1630233',NULL,'DNP - Coach''s Decision',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO GameDetail VALUES('22101005','1610612750','1627774',NULL,'DNP - Coach''s Decision',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO GameDetail VALUES('22101005','1610612748','1629130','F',NULL,'0 0:16:31',1,6,0.167,1,6,0.167,0,0,0,0,0,0,4,0,0,0,3,3,-21);
INSERT INTO GameDetail VALUES('22101005','1610612748','200782','F',NULL,'0 0:23:17',3,7,0.429,0,1,0,0,0,0,4,3,7,0,0,0,3,4,6,-25);
INSERT INTO GameDetail VALUES('22101005','1610612748','1628389','C',NULL,'0 0:33:28',7,12,0.583,0,0,0,5,9,0.556,2,10,12,4,3,0,4,2,19,0);
INSERT INTO GameDetail VALUES('22101005','1610612748','1629216','G',NULL,'0 0:25:23',1,8,0.125,0,5,0,0,0,0,0,1,1,3,2,0,1,2,2,-22);
INSERT INTO GameDetail VALUES('22101005','1610612748','200768','G',NULL,'0 0:37:24',4,12,0.333,2,8,0.25,4,6,0.667,2,5,7,7,0,0,3,2,14,-7);
INSERT INTO GameDetail VALUES('22101005','1610612748','1629639',NULL,NULL,'0 0:36:30',8,19,0.421,6,10,0.6,8,8,1,0,7,7,2,2,0,1,1,30,11);
INSERT INTO GameDetail VALUES('22101005','1610612748','1629622',NULL,NULL,'0 0:31:18',6,12,0.5,5,11,0.455,2,2,1,1,6,7,2,0,0,1,5,19,14);
INSERT INTO GameDetail VALUES('22101005','1610612748','202693',NULL,NULL,'0 0:17:02',3,7,0.429,0,2,0,0,0,0,0,4,4,1,0,0,4,2,6,6);
INSERT INTO GameDetail VALUES('22101005','1610612748','203473',NULL,NULL,'0 0:14:32',1,4,0.25,0,1,0,0,0,0,2,6,8,0,0,1,1,3,2,-9);
INSERT INTO GameDetail VALUES('22101005','1610612748','1629312',NULL,NULL,'0 0:4:36',1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,3,8);
INSERT INTO GameDetail VALUES('22101005','1610612748','2617',NULL,'DNP - Coach''s Decision',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO GameDetail VALUES('22101005','1610612748','1630209',NULL,'DNP - Coach''s Decision',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);


SELECT * FROM BestScorer;


-- 11.)
------







