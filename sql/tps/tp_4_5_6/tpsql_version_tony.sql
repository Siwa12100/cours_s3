\! clear 

--- Question 1
DROP FUNCTION nbRebond;
CREATE FUNCTION nbRebond(match Game.id%TYPE)
RETURNS integer as $$
DECLARE num integer;
BEGIN 
    SELECT sum(ga.rebounds) INTO num
    FROM Game g, GameDetail ga
    WHERE g.id = match AND ga.idGame = g.id AND startPosition is NULL AND ga.rebounds is NOT NULL;

    RETURN num;
END ;
$$ LANGUAGE plpgsql ;


DROP FUNCTION nbRebondCurs;
CREATE FUNCTION nbRebondCurs(match Game.id%TYPE)
RETURNS GameDetail.rebounds%TYPE AS $$ 
DECLARE 
    tot GameDetail.rebounds%TYPE:=0;
    num GameDetail.rebounds%TYPE;
    curs cursor FOR SELECT rebounds FROM GameDetail WHERE startPosition is NULL AND idGame = match AND rebounds is NOT NULL;
BEGIN 
    OPEN curs;
    FETCH curs into num;
    WHILE FOUND LOOP
        tot = tot + num;
        FETCH curs INTO num;
    END LOOP;
    CLOSE curs;
    RETURN tot;
END;
$$ LANGUAGE plpgsql;

/* Question 2
SELECT nbRebond(id)
FROM Game
WHERE dateGame ='2022-3-12';
*/

--- Question 3 
DROP FUNCTION nbRebondDeb;
CREATE FUNCTION nbRebondDeb(match Game.id%TYPE)
RETURNS numeric as $$
DECLARE num numeric:=0;
BEGIN 
    SELECT sum(ga.rebounds) INTO num
    FROM GameDetail ga
    WHERE ga.idGame = match AND startPosition is NOT NULL AND  ga.rebounds is NOT NULL;

    IF num is NULL 
    THEN RETURN 0;
    END IF;
    RETURN num;
END ;
$$ LANGUAGE plpgsql ;

------ SELECT nbRebondDeb('22100979');


/* Question 4*/
SELECT t.abbreviation,t2.abbreviation, g.dateGame, nbRebondDeb(g.id) as nbRebond, t.id, g.id
FROM Game g, Team t, Team t2 
WHERE g.idHomeTeam = t.id AND g.idVisitorTeam = t2.id AND nbRebondDeb(g.id) = (SELECT max(nbRebondDeb(id)) FROM Game);


/* Question 5
SELECT g.id , (nbRebondCurs(g.id) + nbRebondDeb(g.id)) as RBIN, (g.reboundsHome + g.reboundsAway) 
FROM Game g, Team t 
WHERE g.idHomeTeam = t.id AND (nbRebondCurs(g.id) + nbRebondDeb(g.id)) != (g.reboundsHome + g.reboundsAway);

SELECT count(g.id )
FROM Game g, Team t 
WHERE g.idHomeTeam = t.id AND (nbRebondCurs(g.id) + nbRebondDeb(g.id)) != (g.reboundsHome + g.reboundsAway);

*/


/* QUestion 6*/

DROP FUNCTION totptnP;
CREATE FUNCTION totptnP(match Game.id%TYPE, team Team.id%TYPE)
RETURNS numeric as $$
DECLARE num numeric;
BEGIN 
    SELECT sum(g.points) INTO num
    FROM GameDetail g
    WHERE g.idGame = match AND g.idTeam = team AND g.points IS NOT NULL;
    
    IF num is NULL 
    THEN RETURN 0;
    END IF;
    RETURN num;
END;
$$ LANGUAGE plpgsql; 


--SELECT totptnP('41800233','1610612757');



-- Question 7 
/*
SELECT g.id AS match_id, (g.ptsHome + g.ptsAway ) AS pts_actual, (totptnP(g.id, g.idHomeTeam)+totptnP(g.id, g.idVisitorTeam)) AS pts_calculated, g.idHomeTeam
FROM Game g
WHERE ((g.ptsHome+g.ptsAway) != (totptnP(g.id, g.idHomeTeam)+totptnP(g.id,g.idVisitorTeam)));
*/
-- Question 8

/* Sur le match id 12000009 =  Milwaukee Bucks vs Dallas Mavericks  le tot de pts est de 214 points donc les pts de Game sont bon */

-- Question 9

DROP FUNCTION isBestAtHome;

CREATE OR REPLACE FUNCTION isBestAtHome(team_id varchar(10)) RETURNS boolean AS $$
DECLARE
    current_season numeric;
    previous_season numeric;
    home_wins numeric;
    away_wins numeric;
    is_best_at_home boolean;
BEGIN
    SELECT MAX(season) INTO current_season FROM Game;
    previous_season := current_season - 1;

    SELECT COUNT(*)
    INTO home_wins
    FROM Game
    WHERE idHomeTeam = team_id
        AND season = previous_season
        AND homeTeamWins = TRUE;

    SELECT COUNT(*)
    INTO away_wins
    FROM Game
    WHERE idVisitorTeam = team_id
        AND season = previous_season
        AND homeTeamWins = FALSE;

    IF home_wins >= away_wins THEN
        is_best_at_home := TRUE;
    ELSE
        is_best_at_home := FALSE;
    END IF;

    RETURN is_best_at_home;
END;
$$ LANGUAGE plpgsql;


-- Question 10

SELECT isBestAtHome('1610612759') AS best_at_home;
