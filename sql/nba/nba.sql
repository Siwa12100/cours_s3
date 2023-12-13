DROP TABLE IF EXISTS GameDetail, Game, Team, Player CASCADE;

--------------------------

Create Or Replace Function traceBestScorer() Returns trigger AS $$
DECLARE

    ptsActuels numeric;
    ptsMax numeric;
    nbLignes numeric;

BEGIN

    ptsActuels = NEW.points;
    
    SELECT INTO nbLignes COUNT(*)
    FROM BestScorer
    WHERE idGame = NEW.idGame;

    IF nbLignes = 0 THEN
        RAISE NOTICE '[Temporaire] : La game % a % lignes dans BestScorer !', NEW.idGame, nbLignes;
        ptsMax = 0;
    
    ELSE
        RAISE NOTICE '[Temporaire] : La game % a % lignes dans BestScorer !', NEW.idGame, nbLignes;
        SELECT bt.points INTO STRICT ptsMax
        FROM BestScorer bt
        WHERE bt.idGame = NEW.idGame;

    END IF;  

    IF ptsActuels > ptsMax THEN
        IF nbLignes = 0 THEN
            INSERT INTO BestScorer VALUES(ptsActuels, NEW.idPlayer, NEW.idGame);
            RAISE NOTICE 'INSERT Dans % ...', NEW.idGame;
        ELSE
            UPDATE BestScorer 
            SET points = ptsActuels,
            idPlayer = NEW.idPlayer
            WHERE idGame = NEW.idGame;
            RAISE NOTICE 'UPDATE Dans % ...', NEW.idGame;
        END IF;
    END IF;

    RETURN NEW;

END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS triggerBestScorer ON Gamedetail;
CREATE TRIGGER triggerBestScorer BEFORE INSERT ON Gamedetail
FOR EACH ROW
EXECUTE FUNCTION traceBestScorer();

-------------------------------------

CREATE TABLE Player (
       id       varchar(10) PRIMARY KEY,
       name     varchar(50),
       country  varchar(50)
);

CREATE TABLE Team(
       id            varchar(10) PRIMARY KEY,
       abbreviation  char(3),
       nickname      varchar(30),
       city          varchar(30),
       minYear       numeric,
       yearFounded   numeric,
       arena         varchar(30),
       arenaCapacity numeric,
       conference    char(1)
);

CREATE TABLE Game(
       id                    char(8) PRIMARY KEY,
       dateGame              date,
       idHomeTeam            varchar(10) REFERENCES Team, 
       idVisitorTeam         varchar(10) REFERENCES Team,
       season                numeric,
       ptsHome	             numeric,
       fieldGoalsPrctageHome  numeric CHECK(fieldGoalsPrctageHome <=1 AND fieldGoalsPrctageHome >= 0),
       freeThrowsPrctageHome  numeric CHECK(freeThrowsPrctageHome <=1 AND freeThrowsPrctageHome >= 0),
       threePointsPrctageHome numeric CHECK(threePointsPrctageHome <=1 AND threePointsPrctageHome >= 0),
       assistsHome           numeric,
       reboundsHome          numeric,
       ptsAway	             numeric,
       fieldGoalsPrctageAway  numeric CHECK(fieldGoalsPrctageAway <=1 AND fieldGoalsPrctageAway >= 0),
       freeThrowsPrctageAway  numeric CHECK(freeThrowsPrctageAway <=1 AND freeThrowsPrctageAway >= 0),
       threePointsPrctageAway numeric CHECK(threePointsPrctageAway <=1 AND threePointsPrctageAway >= 0),
       assistsAway           numeric,
       reboundsAway          numeric,
       homeTeamWins          boolean
);

CREATE TABLE GameDetail(
  idGame               char(8) REFERENCES Game,
  idTeam               varchar(10) REFERENCES Team,
  idPlayer             varchar(10) REFERENCES Player,
  startPosition        char(1),
  comment              varchar(50),
  playingTime          interval,
  fieldGoalsMade       numeric,
  fieldGoalsAttempted  numeric,
  fieldGoalsPrctage    numeric CHECK(fieldGoalsPrctage <=1 AND fieldGoalsPrctage >= 0),
  threePointsMade      numeric,
  threePointsAttempted numeric,
  threePointsPrctage   numeric CHECK(threePointsPrctage <=1 AND threePointsPrctage >= 0),
  freeThrowsMade       numeric,
  freeThrowsAttempted  numeric,
  freeThrowsPrctage    numeric CHECK(freeThrowsPrctage <=1 AND freeThrowsPrctage >= 0),
  offensiveRebounds    numeric,
  defensiveRebounds    numeric,
  rebounds             numeric,
  assists              numeric,
  steals               numeric,
  blockedShots         numeric,
  turnovers            numeric,
  personnalFoul        numeric,
  points               numeric,
  plusMinus            numeric,
  PRIMARY KEY(idGame, idTeam, idPlayer)
);


\i players.sql
\i teams.sql
\i games.sql
\i games-details.sql
