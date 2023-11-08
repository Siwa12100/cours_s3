-- CREATE OR REPLACE FUNCTION isBestAtHome(equipe Team.id%TYPE, saison Game.season%TYPE) RETURNS BOOLEAN AS $$
-- DECLARE
--     vicExterieur NUMERIC;
--     vicDomicile NUMERIC;
-- BEGIN
--     SELECT COUNT(*) INTO vicDomicile
--     FROM Game g
--     WHERE g.season = saison
--     AND g.idHomeTeam = equipe
--     AND g.homeTeamWins = TRUE;

--     SELECT COUNT(*) INTO vicExterieur
--     FROM Game g
--     WHERE g.season = saison
--     AND g.idVisitorTeam = equipe
--     AND g.homeTeamWins = FALSE;

--     IF vicDomicile >= vicExterieur THEN

--         -- RAISE NOTICE 'Plus de victoires a domicile...';
--         RETURN TRUE;
    
--     ELSE
--         RETURN FALSE;
--     END IF;
-- END;
-- $$ LANGUAGE plpgsql;


-- Question 11 : 
----------------

-- CREATE OR REPLACE FUNCTION bestAtHome(saison Game.season%TYPE) 
-- RETURNS TABLE(id Team.id%TYPE, abbr Team.abbreviation%TYPE) AS $$
-- --DECLARE
-- BEGIN

--     RETURN QUERY SELECT DISTINCT t.id, t.abbreviation
--     FROM Team t 
--     WHERE isBestAtHome(t.id, saison) = TRUE;
-- END;
-- $$ LANGUAGE plpgsql;


-- -- Question 12 : 
-- ----------------
-- SELECT BestAtHome(2021);


-- -- Question 13 : 
-- ----------------


-- -- CREATE OR REPLACE FUNCTION isEgalDomExtN(equipe Team.id%TYPE, n NUMERIC) RETURNS BOOLEAN AS $$
-- -- DECLARE
-- --     cpt NUMERIC := 0;
-- --     NUMERIC saisonMIN;
-- --     NUMERIC parcoursSaison;
-- --     NUMERIC saisonMAX;

-- -- BEGIN
-- --     SELECT MIN(g.season) INTO saisonMIN FROM Game g;
-- --     SELECT MAX(g.season) INTO saisonMAX FROM Gameg;

-- --     parcoursSaison = saisonMIN;

-- --     WHILE (isBestAtHome(equipe, parcoursSaison) AND parcoursSaison <= saisonMAX AND cpt <= n) LOOP
-- --         cpt = cpt + 1;
-- --         parcoursSaison = parcoursSaison + 1;
-- --     END LOOP;

-- --     IF cpt >= 5 THEN 
-- --         RETURN TRUE;
-- --     END IF;

-- --     RETURN FALSE;
-- -- END;
-- -- $$ LANGUAGE plpgsql;



-- -- CREATE OR REPLACE FUNCTION VerifEgalDomExtN(n NUMERIC) RETURNS NUMERIC AS $$
-- -- DECLARE
-- --     cpt NUMERIC :=0;
-- --     curs cursor FOR SELECT t.id FROM Team t;

-- -- BEGIN

-- --     FOR equipe IN curs LOOP

-- --         IF isEgalDomExtN(t, n) THEN
-- --             cpt = cpt + 1;
-- --     END LOOP;
-- -- BEGIN

-- CREATE OR REPLACE FUNCTION check_home_wins(
--     team_name varchar(30),
--     n_seasons numeric
-- ) RETURNS BOOLEAN AS $$
-- DECLARE
--     total_seasons numeric;
--     home_wins numeric;
--     away_wins numeric;
--     current_season numeric;
-- BEGIN
--     -- Vérifier si n est une valeur possible
--     IF n_seasons <= 0 THEN
--         RAISE EXCEPTION 'La valeur de n doit être supérieure à zéro.';
--     END IF;
    
--     -- Obtenir le nombre total de saisons pour l'équipe donnée
--     SELECT COUNT(DISTINCT season) INTO total_seasons
--     FROM Game
--     WHERE idHomeTeam = team_name OR idVisitorTeam = team_name;

--     -- Vérifier si le nombre de saisons consécutives est supérieur au nombre total de saisons
--     IF n_seasons > total_seasons THEN
--         RAISE EXCEPTION 'Le nombre de saisons consécutives demandé dépasse le nombre total de saisons.';
--     END IF;

--     -- Initialiser les compteurs
--     home_wins := 0;
--     away_wins := 0;
--     current_season := NULL;

--     -- Parcourir les matchs pour l'équipe donnée
--     FOR season_rec IN
--         SELECT season, homeTeamWins
--         FROM Game
--         WHERE idHomeTeam = team_name OR idVisitorTeam = team_name
--         ORDER BY season
--     LOOP
--         IF current_season IS NULL OR current_season <> season_rec.season THEN
--             -- Nouvelle saison, réinitialiser les compteurs
--             current_season := season_rec.season;
--             home_wins := 0;
--             away_wins := 0;
--         END IF;

--         IF season_rec.homeTeamWins THEN
--             home_wins := home_wins + 1;
--         ELSE
--             away_wins := away_wins + 1;
--         END IF;

--         -- Vérifier si l'équipe a gagné autant de matchs à domicile qu'à l'extérieur pendant n saisons consécutives
--         IF home_wins >= n_seasons AND away_wins >= n_seasons THEN
--             RETURN TRUE;
--         END IF;
--     END LOOP;

--     -- Si la boucle ne retourne pas TRUE, cela signifie que la condition n'a pas été satisfaite
--     RETURN FALSE;
-- END;
-- $$ LANGUAGE plpgsql;



-- -- Question 14 : 
-- -- =============
-- SELECT id, nickname
-- FROM Team
-- WHERE check_home_wins(id, 2) = TRUE;


-- -- Question 15 : 
-- -- =============
-- CREATE OR REPLACE FUNCTION best_three_point_shooting_team(
--     season_year numeric
-- ) RETURNS varchar(10) AS $$
-- DECLARE
--     best_team_id varchar(10);
-- BEGIN
--     -- Sélectionner l'ID de l'équipe ayant le meilleur pourcentage moyen de paniers à 3 points pour la saison donnée
--     SELECT idTeam
--     INTO best_team_id
--     FROM (
--         SELECT idTeam, AVG(threePointsPrctage) AS avg_3pt_percentage
--         FROM GameDetail gd
--         JOIN Game g ON gd.idGame = g.id
--         WHERE g.season = season_year
--         GROUP BY idTeam
--         ORDER BY avg_3pt_percentage DESC
--         LIMIT 1
--     );

--     RETURN best_team_id;
-- END;
-- $$ LANGUAGE plpgsql;


-- -- Question 16 : 
-- -- =============
-- SELECT
--     t.abbreviation AS abbréviation,
--     t.nickname AS nom,
--     t.city AS ville
-- FROM Team t
-- WHERE t.id = best_three_point_shooting_team(2021);


-- Question 17 : 
-- =============
CREATE OR REPLACE FUNCTION total_three_points_player(player_id Player.id%TYPE, season_year Game.season%TYPE) 
    RETURNS numeric AS $$

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


-- SELECT total_three_points_player('1630195', 2021);



-- Question 18 : 
-- =============

CREATE OR REPLACE FUNCTION best_three_points_player(season_year Game.season%TYPE)
    RETURNS Player.id%TYPE AS $$

    DECLARE
        id_player_max numeric := 0;
        max_points numeric := 0;
        currentId numeric := 0;
        currentPts numeric := 0;

        curs cursor FOR SELECT p.id, total_three_points_player(p.id, g.season)
                        FROM Player p
                        JOIN GameDetail gd ON gd.idPlayer = p.id
                        JOIN Game g ON gd.idGame = g.id
                        WHERE g.season = season_year;
        
        BEGIN
        -- RAISE NOTICE 'debut du begin...';
        
            OPEN curs;
            FETCH curs INTO currentId, currentPts;
            -- RAISE NOTICE 'passage au premier player %(%) | max courant : %', currentId, currentPts, max_points;
            
            WHILE FOUND LOOP

                IF currentPts >= max_points THEN
                    id_player_max = currentId;
                    max_points = currentPts;
                    END IF;

                -- RAISE NOTICE 'passage au player %(%) | max courant : %', currentId, currentPts, max_points;

                FETCH curs INTO currentId, currentPts;
                END LOOP;
            
            CLOSE curs;

        RETURN id_player_max;
    END;
$$ LANGUAGE plpgsql;

 -- SELECT best_three_points_player(2003);


-- Question 19 : 
-- =============


-- DO $$
--     DECLARE
--         current_season numeric := 0;
--         season_min numeric := 0;
--         season_max numeric := 0;
--         -- current_player Player.id%TYPE;
--         maxPts numeric := 0;
--         max_player Player.id%TYPE;

--     BEGIN
--         SELECT MIN(g.season) INTO STRICT season_min
--         FROM Game g;
--         RAISE NOTICE 'La saison minimale est : %', season_min;

--         SELECT MAX(g.season) INTO STRICT season_max
--         FROM Game g;
--         RAISE NOTICE 'La saison maximale est : %', season_max;

--         current_season = season_min;

--         WHILE current_season <= season_max LOOP
            
--             SELECT best_three_points_player(current_season) INTO max_player;
--             SELECT total_three_points_player(max_player, current_season) INTO maxPts;
--             RAISE NOTICE ' -> En % le meilleur joueur (%) a fait %', current_season, max_player, maxPts;
--             current_season = current_season + 1;
--         END LOOP;
--     END;
-- $$;

CREATE TABLE IF NOT EXISTS Stats(
    season numeric,
    player varchar(10),
    threePoints numeric,
    PRIMARY KEY (player, season)
);

DO $$
    DECLARE 
        curs cursor FOR SELECT DISTINCT p.id, g.season, total_three_points_player(p.id, g.season)
                        FROM Player p 
                        JOIN GameDetail gd ON gd.idPlayer = p.id
                        JOIN Game g ON g.id = gd.idGame;
        season numeric;
        player varchar(10);
        threePoints numeric;
    BEGIN
        OPEN curs;
        FETCH curs INTO player, season, threePoints;
        WHILE FOUND LOOP    
            RAISE NOTICE 'Insertion dans Stats du joueur % en saison % ayant fait %', player, season, threePoints;
            INSERT INTO Stats VALUES (season, player, threePoints);
        END LOOP;

        CLOSE curs;
    END;
$$;






