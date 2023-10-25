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


CREATE OR REPLACE FUNCTION isEgalDomExtN(equipe Team.id%TYPE, n NUMERIC) RETURNS BOOLEAN AS $$
DECLARE
    cpt NUMERIC := 0;
    NUMERIC saisonMIN;
    NUMERIC parcoursSaison;
    NUMERIC saisonMAX;

BEGIN
    SELECT MIN(g.season) INTO saisonMIN FROM Game g;
    SELECT MAX(g.season) INTO saisonMAX FROM Gameg;

    parcoursSaison = saisonMIN;

    WHILE (isBestAtHome(equipe, parcoursSaison) AND parcoursSaison <= saisonMAX AND cpt <= n) LOOP
        cpt = cpt + 1;
        parcoursSaison = parcoursSaison + 1;
    END LOOP;

    IF cpt >= 5 THEN 
        RETURN TRUE;
    END IF;

    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION VerifEgalDomExtN(n NUMERIC) RETURNS NUMERIC AS $$
DECLARE
    cpt NUMERIC :=0;
    curs cursor FOR SELECT t.id FROM Team t;

BEGIN

    FOR equipe IN curs LOOP

        IF isEgalDomExtN(t, n) THEN
            cpt = cpt + 1;
    END LOOP;
BEGIN






