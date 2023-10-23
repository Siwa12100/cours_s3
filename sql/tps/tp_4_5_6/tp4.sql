
-- Q.1 | Partie 1 )
------------------
-- DROP FUNCTION IF EXISTS nbRebondsPasDebute_SansCurseur;

CREATE OR REPLACE FUNCTION nbRebondsPasDebute_SansCurseur(game GameDetail.idGame%TYPE) RETURNS Integer AS $$
DECLARE
    cpt integer;

BEGIN
    SELECT SUM(gd.rebounds) INTO cpt
    FROM GameDetail gd
    WHERE gd.startPosition is NULL 
    AND game = gd.idGame;

    -- RAISE NOTICE 'Le nombre de rebonds pour la partie % est : %', game, cpt;
    RETURN cpt;
END;

$$LANGUAGE plpgsql;

-- SELECT nbRebondsPasDebute_SansCurseur('22100979');
-- Résultat : 32



-- Q.1 | Partie 2 )
------------------

-- DROP FUNCTION nbRebondsPasDebute_AvecCurseur;

CREATE OR REPLACE FUNCTION nbRebondsPasDebute_AvecCurseur(game GameDetail.idGame%TYPE) RETURNS Integer AS $$
DECLARE
    cpt integer := 0;
    curs cursor FOR SELECT gd.rebounds FROM GameDetail gd WHERE game = gd.idGame AND startPosition is NULL;

BEGIN

    FOR ligne IN curs LOOP

        IF ligne.rebounds IS NOT NULL THEN
            cpt = cpt + ligne.rebounds;

        END IF;
    END LOOP;

    -- RAISE NOTICE 'Le nombre de rebonds pour la partie % est : %', game, cpt;
    RETURN cpt;
END;
$$ LANGUAGE plpgsql;

-- SELECT nbRebondsPasDebute_AvecCurseur('22100979');
-- Résultat : 32



-- Q.2 )
-------

-- SELECT DISTINCT nbRebondsPasDebute_AvecCurseur(gd.idGame) AS fct_avecCurseur, nbRebondsPasDebute_SansCurseur(gd.idGame) AS fct_avecCurseur
-- FROM GameDetail gd
-- JOIN Game g ON g.id = gd.idGame
-- WHERE g.dateGame = '12-03-2022';



-- Q.3 )
-------
-- DROP FUNCTION nbRebondsDebute;

CREATE OR REPLACE FUNCTION nbRebondsDebute(game GameDetail.idGame%TYPE) RETURNS Integer AS $$
DECLARE
    cpt integer;

BEGIN
    SELECT SUM(gd.rebounds) INTO cpt
    FROM GameDetail gd
    WHERE gd.startPosition is NOT NULL 
    AND game = gd.idGame;

    -- RAISE NOTICE 'Le nombre de rebonds pour la partie % est : %', game, cpt;
    RETURN cpt;
END;

$$LANGUAGE plpgsql;

-- SELECT nbRebondsDebute('22100979');
-- Résultat : 57 



-- Q.4 )
-------
-- A reprendre sans le limit 
-- SELECT g.id, tH.abbreviation, tV.abbreviation, g.dateGame, nbRebondsDebute(gd.idGame) 
-- FROM Game g 
-- JOIN GameDetail gd ON g.id = gd.idGame
-- JOIN Team tH ON tH.id = g.idHomeTeam
-- JOIN Team tV ON tV.id = g.idVisitorTeam
-- WHERE nbRebondsDebute(gd.idGame) is NOT NULL
-- ORDER BY 5 DESC
-- LIMIT 1;

SELECT g.dateGame, g.id, homeTeam.abbreviation AS homeTeamAbbreviation, visitorTeam.abbreviation AS visitorTeamAbbreviation
FROM Game g
JOIN Team homeTeam ON g.idHomeTeam = homeTeam.id
JOIN Team visitorTeam ON g.idVisitorTeam = visitorTeam.id
WHERE (
    SELECT SUM(gd.rebounds)
    FROM GameDetail gd
    WHERE gd.startPosition IS NOT NULL
    AND gd.idGame = g.id
) = (
    SELECT MAX(totalRebounds)
    FROM (
        SELECT gd.idGame, SUM(gd.rebounds) AS totalRebounds
        FROM GameDetail gd
        WHERE gd.startPosition IS NOT NULL
        GROUP BY gd.idGame
    ) AS Subquery
);



-- Résultat : 
    -- id : 41800233
    -- nbRebonds : 101 


-- Q.5 )
-------
-- SELECT DISTINCT gd.idGame, (g.reboundsHome + g.reboundsAway) AS tot_game, 
--        (nbRebondsDebute(gd.idGame) + nbRebondsPasDebute_SansCurseur(gd.idGame)) as tot_gamedetail
-- FROM Game g
-- JOIN GameDetail gd ON g.id = gd.idGame
-- WHERE nbRebondsDebute(gd.idGame) IS NOT NULL
-- AND nbRebondsPasDebute_SansCurseur(gd.idGame) IS NOT NULL
-- GROUP BY gd.idGame, g.reboundsAway, g.reboundsHome
-- hAVING (g.reboundsHome + g.reboundsAway) != (nbRebondsDebute(gd.idGame) + nbRebondsPasDebute_SansCurseur(gd.idGame));


-- Q.6 )
-------
-- CREATE OR REPLACE FUNCTION totalPointsEquipe(game Game.id%TYPE, team Team.id%TYPE) RETURNS Integer AS $$
-- DECLARE

-- BEGIN
--     cpt integer := 0;
--     curs cursor FOR SELECT gd.points
--                     FROM GameDetail gd 
--                     JOIN Game g ON g.id = idGame
--                     WHERE 
-- END;

-- $$LANGUAGE plpgsql;







