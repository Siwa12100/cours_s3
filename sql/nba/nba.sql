DROP TABLE IF EXISTS GameDetail, Game, Team, Player CASCADE;

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
