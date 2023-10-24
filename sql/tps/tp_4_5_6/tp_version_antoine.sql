-- Rebonds

-- 1
-- Fonction avec agrégation
CREATE OR REPLACE FUNCTION rebonds1(match game.id%TYPE)
RETURNS GameDetail.rebounds%TYPE as $$

DECLARE
    totalRebound integer;
    BEGIN
        SELECT sum(rebounds) INTO totalRebound
        FROM GameDetail
        WHERE StartPosition is NULL AND idGame = match;

        RETURN totalRebound;
    END;
$$ LANGUAGE PLPGSQL;

-- Fonction avec curseur

CREATE OR REPLACE FUNCTION rebonds2(match game.id%TYPE)
RETURNS GameDetail.rebounds%TYPE as $$

DECLARE
    totalRebound GameDetail.rebounds%TYPE:=0;
    a GameDetail.rebounds%TYPE;
    curs cursor FOR SELECT rebounds
                    FROM GameDetail
                    WHERE StartPosition is NULL AND idGame = match AND rebounds IS NOT NULL;
    BEGIN
        OPEN curs;
        FETCH curs into a;
        WHILE FOUND LOOP
            totalRebound = totalRebound + a;
            FETCH curs into a;
        END LOOP;
        CLOSE curs;
        RETURN totalRebound;
    END;
$$ LANGUAGE PLPGSQL;

SELECT rebonds1('22100979'), rebonds2('22100979');

-- 2 

SELECT rebonds1(id)
FROM Game
WHERE dateGame = '2022-03-12';

-- 3 

CREATE OR REPLACE FUNCTION rebondsTitulaire(match game.id%TYPE)
RETURNS GameDetail.rebounds%TYPE as $$

DECLARE
    totalRebound GameDetail.rebounds%TYPE:=0;
    a GameDetail.rebounds%TYPE;
    curs cursor FOR SELECT rebounds
                    FROM GameDetail
                    WHERE StartPosition is NOT NULL AND idGame = match AND rebounds IS NOT NULL;
    BEGIN
        OPEN curs;
        FETCH curs into a;
        WHILE FOUND LOOP
            totalRebound = totalRebound + a;
            FETCH curs into a;
        END LOOP;
        CLOSE curs;
        RETURN totalRebound;
    END;
$$ LANGUAGE PLPGSQL;

SELECT rebondsTitulaire('22100979');

-- 4 

SELECT t1.abbreviation as Home, t2.abbreviation as Visitor, dateGame, rebondsTitulaire(Game.id) as NbRebonds
FROM Game, Team t1, Team t2
WHERE Game.idHomeTeam=t1.id AND Game.idVisitorTeam=t2.id AND rebondsTitulaire(Game.id) = (SELECT MAX(rebondsTitulaire(id))
                                                                                          FROM Game);

-- Verification des données

-- 5

SELECT id, (reboundsHome + reboundsAway) as NbRebondsMatch, (rebonds2(id)+rebondsTitulaire(id)) as NbRebondsJoueurs
FROM Game
WHERE (reboundsHome + reboundsAway) != (rebonds1(id)+rebondsTitulaire(id))
ORDER BY id ASC;

-- 6

CREATE OR REPLACE FUNCTION nbPointsTeam(match GameDetail.idGame%TYPE, team Team.id%TYPE)
RETURNS GameDetail.points%TYPE AS $$

DECLARE
    totalPoints GameDetail.points%TYPE:=0;
    a GameDetail.points%TYPE;
    curs cursor FOR SELECT points FROM GameDetail WHERE match = GameDetail.idGame AND team = GameDetail.idTeam AND GameDetail.points is NOT NULL;

    BEGIN
    OPEN curs;
    FETCH curs INTO a;
    WHILE FOUND LOOP
        totalPoints = totalPoints + a;
        FETCH curs INTO a;
    END LOOP;
    CLOSE curs;
    RETURN totalPoints;
END;
$$ LANGUAGE PLPGSQL;

SELECT nbPointsTeam('41800233','1610612757') as TotalPoints;

-- 7

SELECT id
FROM Game
WHERE nbPointsTeam(id, idVisitorTeam) != ptsAway OR nbPointsTeam(id, idHomeTeam) != ptsHome
ORDER BY id ASC;

-- 8

SELECT id, ptsAway as GameVisitor, ptsHome as GameHome, nbPointsTeam(id, idVisitorTeam) as GameDetailVisitor, nbPointsTeam(id, idHomeTeam) as GameDetailHome
FROM Game
WHERE nbPointsTeam(id, idVisitorTeam) != ptsAway OR nbPointsTeam(id, idHomeTeam) != ptsHome
ORDER BY id ASC;

/*
On peut voir que la table GameDetail ne correspond pas aux résultats des points par équipe dans la table Game. Chaques résultats obtenu est inférieur aux résultats de la table Game.
Ainsi, on peut conclure que GameDetail est incorrecte.
*/

-- Domicile VS Extérieur

-- 9

CREATE OR REPLACE FUNCTION isBestAtHome(team Team.id%TYPE, saison Game.season%TYPE)
RETURNS Boolean as $$

DECLARE
    sumEXT integer:=0;
    sumDOM integer:=0;
    a Game.homeTeamWins%TYPE;
    b Game.homeTeamWins%TYPE;
    curs1 cursor FOR SELECT homeTeamWins 
                     FROM Game 
                     WHERE idHomeTeam = team AND season = saison; 
    curs2 cursor FOR SELECT homeTeamWins 
                     FROM Game 
                     WHERE idVisitorTeam = team AND season = saison;
    BEGIN 
        OPEN curs1;
        FETCH curs1 INTO a;
        WHILE FOUND LOOP
            IF (a = 't') THEN
                sumDOM = sumDOM + 1;
                END IF;
            FETCH curs1 INTO a;
        END LOOP;
        CLOSE curs1;
        OPEN curs2;
        FETCH curs2 INTO b;
        WHILE FOUND LOOP
            IF (b = 'f') THEN
                sumEXT = sumEXT + 1;
                END IF;
            FETCH curs2 INTO b;
        END LOOP;
        CLOSE curs2;
        IF (sumDOM>=sumEXT) THEN 
            RETURN 1;
        ELSE
            RETURN 0;
        END IF;
    END;
$$ LANGUAGE PLPGSQL;


-- 10

SELECT isBestAtHome('1610612747', 2021);