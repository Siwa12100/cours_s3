-- -- Réponse à la Question 1, Partie 1 
-- CREATE OR REPLACE FUNCTION calculerRebondsNonDebute_SansCurseur(match GameDetail.idGame%TYPE) RETURNS INTEGER AS $$
-- DECLARE
--     totalRebonds INTEGER;
-- BEGIN
--     SELECT SUM(gd.rebonds) INTO totalRebonds
--     FROM GameDetail gd
--     WHERE gd.startPosition IS NULL 
--     AND match = gd.idGame;
    
--     RETURN totalRebonds;
-- END;
-- $$ LANGUAGE plpgsql;

-- -- Réponse à la Question 1, Partie 2 
-- CREATE OR REPLACE FUNCTION calculerRebondsNonDebute_AvecCurseur(match GameDetail.idGame%TYPE) RETURNS INTEGER AS $$
-- DECLARE
--     totalRebonds INTEGER := 0;
--     valeurRebond INTEGER;
--     cur CURSOR FOR SELECT gd.rebonds FROM GameDetail gd WHERE match = gd.idGame AND gd.startPosition IS NULL;
-- BEGIN
--     OPEN cur;
--     FETCH cur INTO valeurRebond;
--     WHILE FOUND LOOP
--         IF valeurRebond IS NOT NULL THEN
--             totalRebonds := totalRebonds + valeurRebond;
--         END IF;
--         FETCH cur INTO valeurRebond;
--     END LOOP;
--     CLOSE cur;
    
--     RETURN totalRebonds;
-- END;
-- $$ LANGUAGE plpgsql;

-- -- Réponse à la Question 2 
-- SELECT calculerRebondsNonDebute_SansCurseur(gd.idGame) AS totalRebondsSansCurseur, calculerRebondsNonDebute_AvecCurseur(gd.idGame) AS totalRebondsAvecCurseur
-- FROM GameDetail gd
-- JOIN Game g ON g.id = gd.idGame
-- WHERE g.dateGame = '12-03-2022';

-- -- Réponse à la Question 3 
-- CREATE OR REPLACE FUNCTION calculerRebondsCommence(match GameDetail.idGame%TYPE) RETURNS INTEGER AS $$
-- DECLARE
--     totalRebonds INTEGER;
-- BEGIN
--     SELECT SUM(gd.rebonds) INTO totalRebonds
--     FROM GameDetail gd
--     WHERE gd.startPosition IS NOT NULL 
--     AND match = gd.idGame;
    
--     RETURN totalRebonds;
-- END;
-- $$ LANGUAGE plpgsql;

-- -- Réponse à la Question 4 
-- SELECT t1.abbreviation AS AbbrEquipeDomicile, t2.abbreviation AS AbbrEquipeVisiteur, g.dateGame, calculerRebondsCommence(gd.idGame) AS totalRebondsCommence
-- FROM Game g, Team t1, Team t2, GameDetail gd
-- WHERE g.idHomeTeam = t1.id AND g.idVisitorTeam = t2.id AND gd.idGame = g.id AND calculerRebondsCommence(gd.idGame) = (
--     SELECT MAX(calculerRebondsCommence(gd.idGame))
--     FROM GameDetail gd
-- );

-- -- Réponse à la Question 5 
-- SELECT g.id AS IDMatch, (calculerRebondsNonDebute_AvecCurseur(g.id) + calculerRebondsCommence(g.id)) AS RebondsDepuisFonctions, (g.rebondsDomicile + g.rebondsExterieur) AS TotalRebondsDepuisMatch
-- FROM Game g, Team t
-- WHERE g.idHomeTeam = t.id AND (calculerRebondsNonDebute_AvecCurseur(g.id) + calculerRebondsCommence(g.id)) != (g.rebondsDomicile + g.rebondsExterieur);

-- -- Réponse à la Question 6 
-- CREATE OR REPLACE FUNCTION calculerTotalPointsPourEquipe(match GameDetail.idGame%TYPE, equipe Team.id%TYPE) RETURNS NUMERIC AS $$
-- DECLARE
--     totalPoints NUMERIC;
-- BEGIN
--     SELECT SUM(gd.points) INTO totalPoints
--     FROM GameDetail gd
--     WHERE gd.idGame = match AND gd.idTeam = equipe AND gd.points IS NOT NULL;
    
--     RETURN totalPoints;
-- END;
-- $$ LANGUAGE plpgsql;

-- -- Réponse à la Question 7 
-- SELECT g.id AS IDMatch, (g.ptsDomicile + g.ptsExterieur) AS TotalPointsDepuisMatch, (calculerTotalPointsPourEquipe(g.id, g.idHomeTeam) + calculerTotalPointsPourEquipe(g.id, g.idVisitorTeam)) AS TotalPointsCalcules
-- FROM Game g
-- WHERE (g.ptsDomicile + g.ptsExterieur) != (calculerTotalPointsPourEquipe(g.id, g.idHomeTeam) + calculerTotalPointsPourEquipe(g.id, g.idVisitorTeam));

-- -- Réponse à la Question 8 
-- SELECT g.id AS IDMatch, g.ptsDomicile AS PointsEquipeDomicileMatch, g.ptsExterieur AS PointsEquipeVisiteurMatch, 
--        calculerTotalPointsPourEquipe(g.id, g.idHomeTeam) AS PointsEquipeDomicileDetail, 
--        calculerTotalPointsPourEquipe(g.id, g.idVisitorTeam) AS PointsEquipeVisiteurDetail
-- FROM Game g
-- WHERE (g.ptsDomicile != calculerTotalPointsPourEquipe(g.id, g.idHomeTeam)) OR (g.ptsExterieur != calculerTotalPointsPourEquipe(g.id, g.idVisitorTeam));

-- Réponse à la Question 9 : 

-- CREATE OR REPLACE FUNCTION estMeilleureADomicileSaisonPrecedente(equipe Team.id%TYPE) RETURNS BOOLEAN AS $$
-- DECLARE
--     saisonCourante NUMERIC;
--     saisonPrecedente NUMERIC;
--     victoiresADomicile NUMERIC;
--     victoiresALExterieur NUMERIC;
--     estMeilleureADomicile BOOLEAN;
-- BEGIN
--     SELECT MAX(season) INTO saisonCourante FROM Game;
--     saisonPrecedente := saisonCourante - 1;

--     SELECT COUNT(*) INTO victoiresADomicile
--     FROM Game
--     WHERE idHomeTeam = equipe
--         AND season = saisonPrecedente
--         AND equipeDomicileGagne = TRUE;

--     SELECT COUNT(*) INTO victoiresALExterieur
--     FROM Game
--     WHERE idVisitorTeam = equipe
--         AND season = saisonPrecedente
--         AND equipeDomicileGagne = FALSE;

--     IF victoiresADomicile >= victoiresALExterieur THEN
--         estMeilleureADomicile := TRUE;
--     ELSE
--         estMeilleureADomicile := FALSE;
--     END IF;

--     RETURN estMeilleureADomicile;
-- END;
-- $$ LANGUAGE plpgsql;



-- -- Question 10 : 

-- SELECT estMeilleureADomicileSaisonPrecedente('1610612759') AS EstMeilleureADomicileSaisonPrecedente;




-- Reprise Question 9 : 
----------------------

CREATE OR REPLACE FUNCTION isBestAtHome(equipe Team.id%TYPE, saison Game.season%TYPE) RETURNS BOOLEAN AS $$
DECLARE
    vicExterieur NUMERIC;
    vicDomicile NUMERIC;
BEGIN
    SELECT COUNT(*) INTO vicDomicile
    FROM Game g
    WHERE g.season = saison
    AND t.id = equipe
    AND g.homeTeamWins = TRUE;

    SELECT COUNT(*) INTO vicExterieur
    FROM Game g
    WHERE g.season = saison
    AND t.id = equipe
    AND g.homeTeamWins = FALSE;

    IF vicDomicile >= vicExterieur THEN

        -- RAISE NOTICE 'Plus de victoires a domicile...';
        RETURN TRUE;
    
    ELSE
        RETURN FALSE;
    END IF;
END;
$$ LANGUAGE plpgsql;


-- Reprise Question 10 :
------------------------ 
SELECT isBestAtHome(t.id,2021)
FROM Team t
WHERE t.nickname = 'Spurs';

-- SELECT False;



