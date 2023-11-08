CREATE OR REPLACE FUNCTION isBestAtHome(equipe Team.id%TYPE, saison Game.season%TYPE) RETURNS BOOLEAN AS $$
DECLARE
    vicExterieur NUMERIC;
    vicDomicile NUMERIC;
BEGIN
    SELECT COUNT(*) INTO vicDomicile
    FROM Game g
    WHERE g.season = saison
    AND g.idHomeTeam = equipe
    AND g.homeTeamWins = TRUE;

    SELECT COUNT(*) INTO vicExterieur
    FROM Game g
    WHERE g.season = saison
    AND g.idVisitorTeam = equipe
    AND g.homeTeamWins = FALSE;

    IF vicDomicile >= vicExterieur THEN

        -- RAISE NOTICE 'Plus de victoires a domicile...';
        RETURN TRUE;
    
    ELSE
        RETURN FALSE;
    END IF;
END;
$$ LANGUAGE plpgsql;


-- Question 11 : 
----------------

CREATE OR REPLACE FUNCTION bestAtHome(saison Game.season%TYPE) 
RETURNS TABLE(id Team.id%TYPE, abbr Team.abbreviation%TYPE) AS $$
--DECLARE
BEGIN

    RETURN QUERY SELECT DISTINCT t.id, t.abbreviation
    FROM Team t 
    WHERE isBestAtHome(t.id, saison) = TRUE;
END;
$$ LANGUAGE plpgsql;


-- Question 12 : 
----------------
SELECT BestAtHome(2021);


-- Question 13 : 
----------------


-- CREATE OR REPLACE FUNCTION isEgalDomExtN(equipe Team.id%TYPE, n NUMERIC) RETURNS BOOLEAN AS $$
-- DECLARE
--     cpt NUMERIC := 0;
--     NUMERIC saisonMIN;
--     NUMERIC parcoursSaison;
--     NUMERIC saisonMAX;

-- BEGIN
--     SELECT MIN(g.season) INTO saisonMIN FROM Game g;
--     SELECT MAX(g.season) INTO saisonMAX FROM Gameg;

--     parcoursSaison = saisonMIN;

--     WHILE (isBestAtHome(equipe, parcoursSaison) AND parcoursSaison <= saisonMAX AND cpt <= n) LOOP
--         cpt = cpt + 1;
--         parcoursSaison = parcoursSaison + 1;
--     END LOOP;

--     IF cpt >= 5 THEN 
--         RETURN TRUE;
--     END IF;

--     RETURN FALSE;
-- END;
-- $$ LANGUAGE plpgsql;



-- CREATE OR REPLACE FUNCTION VerifEgalDomExtN(n NUMERIC) RETURNS NUMERIC AS $$
-- DECLARE
--     cpt NUMERIC :=0;
--     curs cursor FOR SELECT t.id FROM Team t;

-- BEGIN

--     FOR equipe IN curs LOOP

--         IF isEgalDomExtN(t, n) THEN
--             cpt = cpt + 1;
--     END LOOP;
-- BEGIN

CREATE OR REPLACE FUNCTION check_home_wins(
    team_name varchar(30),
    n_seasons numeric
) RETURNS BOOLEAN AS $$
DECLARE
    total_seasons numeric;
    home_wins numeric;
    away_wins numeric;
    current_season numeric;
BEGIN
    -- Vérifier si n est une valeur possible
    IF n_seasons <= 0 THEN
        RAISE EXCEPTION 'La valeur de n doit être supérieure à zéro.';
    END IF;
    
    -- Obtenir le nombre total de saisons pour l'équipe donnée
    SELECT COUNT(DISTINCT season) INTO total_seasons
    FROM Game
    WHERE idHomeTeam = team_name OR idVisitorTeam = team_name;

    -- Vérifier si le nombre de saisons consécutives est supérieur au nombre total de saisons
    IF n_seasons > total_seasons THEN
        RAISE EXCEPTION 'Le nombre de saisons consécutives demandé dépasse le nombre total de saisons.';
    END IF;

    -- Initialiser les compteurs
    home_wins := 0;
    away_wins := 0;
    current_season := NULL;

    -- Parcourir les matchs pour l'équipe donnée
    FOR season_rec IN
        SELECT season, homeTeamWins
        FROM Game
        WHERE idHomeTeam = team_name OR idVisitorTeam = team_name
        ORDER BY season
    LOOP
        IF current_season IS NULL OR current_season <> season_rec.season THEN
            -- Nouvelle saison, réinitialiser les compteurs
            current_season := season_rec.season;
            home_wins := 0;
            away_wins := 0;
        END IF;

        IF season_rec.homeTeamWins THEN
            home_wins := home_wins + 1;
        ELSE
            away_wins := away_wins + 1;
        END IF;

        -- Vérifier si l'équipe a gagné autant de matchs à domicile qu'à l'extérieur pendant n saisons consécutives
        IF home_wins >= n_seasons AND away_wins >= n_seasons THEN
            RETURN TRUE;
        END IF;
    END LOOP;

    -- Si la boucle ne retourne pas TRUE, cela signifie que la condition n'a pas été satisfaite
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;



-- Question 14 : 
-- =============
SELECT id, nickname
FROM Team
WHERE check_home_wins(id, 2) = TRUE;


-- Question 15 : 
-- =============
CREATE OR REPLACE FUNCTION best_three_point_shooting_team(
    season_year numeric
) RETURNS varchar(10) AS $$
DECLARE
    best_team_id varchar(10);
BEGIN
    -- Sélectionner l'ID de l'équipe ayant le meilleur pourcentage moyen de paniers à 3 points pour la saison donnée
    SELECT idTeam
    INTO best_team_id
    FROM (
        SELECT idTeam, AVG(threePointsPrctage) AS avg_3pt_percentage
        FROM GameDetail gd
        JOIN Game g ON gd.idGame = g.id
        WHERE g.season = season_year
        GROUP BY idTeam
        ORDER BY avg_3pt_percentage DESC
        LIMIT 1
    );

    RETURN best_team_id;
END;
$$ LANGUAGE plpgsql;


-- Question 16 : 
-- =============
SELECT
    t.abbreviation AS abbréviation,
    t.nickname AS nom,
    t.city AS ville
FROM Team t
WHERE t.id = best_three_point_shooting_team(2021);


-- Question 17 : 
-- =============
CREATE OR REPLACE FUNCTION total_three_pointers_made_by_player(
    player_id varchar(10),
    season_year numeric
) RETURNS numeric AS $$
DECLARE
    total_3pt_made numeric;
BEGIN
    -- Calculer le nombre total de paniers à trois points marqués par le joueur pour la saison donnée
    SELECT SUM(gd.threePointsMade)
    INTO total_3pt_made
    FROM GameDetail gd
    JOIN Game g ON gd.idGame = g.id
    WHERE gd.idPlayer = player_id
        AND g.season = season_year;

    -- Si le joueur n'a pas marqué de paniers à trois points, définir le total à zéro
    IF total_3pt_made IS NULL THEN
        total_3pt_made := 0;
    END IF;

    RETURN total_3pt_made;
END;
$$ LANGUAGE plpgsql;


-- Question 18 : 
-- =============
CREATE OR REPLACE FUNCTION player_with_most_three_pointers(
    season_year numeric
) RETURNS varchar(10) AS $$
DECLARE
    top_player_id varchar(10);
BEGIN
    -- Sélectionner l'ID du joueur ayant marqué le plus de paniers à trois points pour la saison donnée
    SELECT idPlayer
    INTO top_player_id
    FROM (
        SELECT idPlayer, SUM(threePointsMade) AS total_3pt_made
        FROM GameDetail gd
        JOIN Game g ON gd.idGame = g.id
        WHERE g.season = season_year
        GROUP BY idPlayer
        ORDER BY total_3pt_made DESC
        LIMIT 1
    );

    RETURN top_player_id;
END;
$$ LANGUAGE plpgsql;





