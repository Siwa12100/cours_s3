-- Réponse à la Question 1, Partie 1 (Inspiration de Tony)
CREATE OR REPLACE FUNCTION calculateReboundsNotStarted_NoCursor(game GameDetail.idGame%TYPE) RETURNS INTEGER AS $$
DECLARE
    totalRebounds INTEGER;
BEGIN
    SELECT SUM(gd.rebounds) INTO totalRebounds
    FROM GameDetail gd
    WHERE gd.startPosition IS NULL 
    AND game = gd.idGame;
    
    RETURN totalRebounds;
END;
$$ LANGUAGE plpgsql;

-- Réponse à la Question 1, Partie 2 (Inspiration de Tony)
CREATE OR REPLACE FUNCTION calculateReboundsNotStarted_WithCursor(game GameDetail.idGame%TYPE) RETURNS INTEGER AS $$
DECLARE
    totalRebounds INTEGER := 0;
    reboundValue INTEGER;
    cur CURSOR FOR SELECT gd.rebounds FROM GameDetail gd WHERE game = gd.idGame AND gd.startPosition IS NULL;
BEGIN
    OPEN cur;
    FETCH cur INTO reboundValue;
    WHILE FOUND LOOP
        IF reboundValue IS NOT NULL THEN
            totalRebounds := totalRebounds + reboundValue;
        END IF;
        FETCH cur INTO reboundValue;
    END LOOP;
    CLOSE cur;
    
    RETURN totalRebounds;
END;
$$ LANGUAGE plpgsql;

-- Réponse à la Question 2 (Inspiration de Tony)
SELECT calculateReboundsNotStarted_NoCursor(gd.idGame) AS totalReboundsNoCursor, calculateReboundsNotStarted_WithCursor(gd.idGame) AS totalReboundsWithCursor
FROM GameDetail gd
JOIN Game g ON g.id = gd.idGame
WHERE g.dateGame = '12-03-2022';

-- Réponse à la Question 3 (Inspiration de Tony)
CREATE OR REPLACE FUNCTION calculateReboundsStarted(game GameDetail.idGame%TYPE) RETURNS INTEGER AS $$
DECLARE
    totalRebounds INTEGER;
BEGIN
    SELECT SUM(gd.rebounds) INTO totalRebounds
    FROM GameDetail gd
    WHERE gd.startPosition IS NOT NULL 
    AND game = gd.idGame;
    
    RETURN totalRebounds;
END;
$$ LANGUAGE plpgsql;

-- Réponse à la Question 4 (Inspiration de Tony)
SELECT t1.abbreviation AS HomeTeamAbbr, t2.abbreviation AS VisitorTeamAbbr, g.dateGame, calculateReboundsStarted(gd.idGame) AS totalStartedRebounds
FROM Game g, Team t1, Team t2, GameDetail gd
WHERE g.idHomeTeam = t1.id AND g.idVisitorTeam = t2.id AND gd.idGame = g.id AND calculateReboundsStarted(gd.idGame) = (
    SELECT MAX(calculateReboundsStarted(gd.idGame))
    FROM GameDetail gd
);

-- Réponse à la Question 5 (Inspiration de Tony)
SELECT g.id AS GameID, (calculateReboundsNotStarted_WithCursor(g.id) + calculateReboundsStarted(g.id)) AS ReboundsFromFunctions, (g.reboundsHome + g.reboundsAway) AS TotalReboundsFromGame
FROM Game g, Team t
WHERE g.idHomeTeam = t.id AND (calculateReboundsNotStarted_WithCursor(g.id) + calculateReboundsStarted(g.id)) != (g.reboundsHome + g.reboundsAway);


-- Réponse à la Question 6 (Inspiration : Tony)
-- Fonction pour calculer le total des points des joueurs d'une équipe pour un match donné
CREATE OR REPLACE FUNCTION calculateTotalPointsForTeam(match GameDetail.idGame%TYPE, team Team.id%TYPE) RETURNS NUMERIC AS $$
DECLARE
    totalPoints NUMERIC;
BEGIN
    SELECT SUM(gd.points) INTO totalPoints
    FROM GameDetail gd
    WHERE gd.idGame = match AND gd.idTeam = team AND gd.points IS NOT NULL;
    
    RETURN totalPoints;
END;
$$ LANGUAGE plpgsql;

-- Réponse à la Question 7 (Inspiration : Tony)
-- Comparaison des points calculés avec les points de la table Game
SELECT g.id AS GameID, (g.ptsHome + g.ptsAway) AS TotalPointsFromGame, (calculateTotalPointsForTeam(g.id, g.idHomeTeam) + calculateTotalPointsForTeam(g.id, g.idVisitorTeam)) AS TotalPointsCalculated
FROM Game g
WHERE (g.ptsHome + g.ptsAway) != (calculateTotalPointsForTeam(g.id, g.idHomeTeam) + calculateTotalPointsForTeam(g.id, g.idVisitorTeam));

-- Réponse à la Question 8 (Inspiration : Tony)
-- Comparaison détaillée des points entre Game et GameDetail pour chaque match
SELECT g.id AS GameID, g.ptsHome AS GameHomePoints, g.ptsAway AS GameVisitorPoints, 
       calculateTotalPointsForTeam(g.id, g.idHomeTeam) AS GameDetailHomePoints, 
       calculateTotalPointsForTeam(g.id, g.idVisitorTeam) AS GameDetailVisitorPoints
FROM Game g
WHERE (g.ptsHome != calculateTotalPointsForTeam(g.id, g.idHomeTeam)) OR (g.ptsAway != calculateTotalPointsForTeam(g.id, g.idVisitorTeam));

-- Réponse à la Question 9 (Inspiration : Tony)
-- Fonction pour déterminer si une équipe a été meilleure à domicile qu'à l'extérieur la saison précédente
CREATE OR REPLACE FUNCTION isBestAtHomePreviousSeason(team Team.id%TYPE) RETURNS BOOLEAN AS $$
DECLARE
    currentSeason NUMERIC;
    previousSeason NUMERIC;
    homeWins NUMERIC;
    awayWins NUMERIC;
    isBestAtHome BOOLEAN;
BEGIN
    SELECT MAX(season) INTO currentSeason FROM Game;
    previousSeason := currentSeason - 1;

    SELECT COUNT(*) INTO homeWins
    FROM Game
    WHERE idHomeTeam = team
        AND season = previousSeason
        AND homeTeamWins = TRUE;

    SELECT COUNT(*) INTO awayWins
    FROM Game
    WHERE idVisitorTeam = team
        AND season = previousSeason
        AND homeTeamWins = FALSE;

    IF homeWins >= awayWins THEN
        isBestAtHome := TRUE;
    ELSE
        isBestAtHome := FALSE;
    END IF;

    RETURN isBestAtHome;
END;
$$ LANGUAGE plpgsql;

-- Réponse à la Question 10 (Inspiration : Tony)
-- Vérification si l'équipe des Spurs a été meilleure à domicile qu'à l'extérieur la saison précédente
SELECT isBestAtHomePreviousSeason('1610612759') AS IsBestAtHome;

