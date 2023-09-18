/* Question 2 : 
--------------- */ 
-- SELECT t.city 
-- FROM Team t 
-- WHERE t.nickname = 'Grizzlies';


/* Question 3 : 
--------------- */
-- SELECT MAX(g.ptsHome)
-- FROM Game g; 


/* Question 4 : 
--------------- */ 
-- SELECT MAX(g.ptsAway)
-- FROM Game g;


/* Question 5 : 
--------------- */ 
-- SELECT (SELECT t.nickname
--         FROM Team t 
--         JOIN Game g ON t.id = g.idHomeTeam
--         WHERE g.ptsHome = (SELECT MAX(g1.ptsHome) FROM Game g1)), 

--         (SELECT t.nickname
--         FROM Team t 
--         JOIN Game g ON t.id = g.idVisitorTeam
--         WHERE g.ptsAway = (SELECT MAX(g1.ptsAway) FROM Game g1));


/* Question 6 : 
--------------- */ 
-- SELECT t.nickname Nom, t.id ID, t.city, g.dateGame Date_match, g.ptsHome Points_marques
--         FROM Team t 
--         JOIN Game g ON t.id = g.idHomeTeam
--         WHERE g.ptsHome = (SELECT MAX(g1.ptsHome) FROM Game g1);



/* Question 7 : 
--------------- */ 
-- SELECT t.nickname Nom, t.id ID, t.city, g.dateGame Date_match, g.ptsHome Points_marques
--         FROM Team t 
--         JOIN Game g ON t.id = g.idVisitorTeam
--         WHERE g.ptsAway = (SELECT MAX(g1.ptsAway) FROM Game g1);


/* Question 8 : 
--------------- */ 
-- SELECT DISTINCT p.name 
-- FROM GameDetail gd 
-- JOIN Player p ON p.id = gd.idPlayer
-- WHERE gd.threePointsPrctage = (SELECT MAX(gd1.threePointsPrctage) FROM GameDetail gd1);


/* Question 9 : 
--------------- */
-- SELECT p.name 
-- FROM GameDetail gd 
-- JOIN Player p ON p.id = gd.idPlayer
-- WHERE gd.threePointsPrctage IS NOT NULL
-- GROUP BY gd.idPlayer, p.name
-- HAVING AVG(gd.threePointsPrctage) >= ALL(SELECT AVG(gd1.threePointsPrctage)
--                                   FROM GameDetail gd1
--                                   WHERE gd1.threePointsPrctage IS NOT NULL
--                                   GROUP BY gd1.idPlayer);



/* Question 10 : 
--------------- */
-- SELECT MAX(gd.threePointsMade) max_paniers, g.dateGame date
-- FROM GAMEDETAIL gd
-- JOIN GAME g ON gd.idGame = g.id
-- WHERE Extract(YEAR FROM g.dateGame) = 2012
-- GROUP BY g.dateGame;

SELECT gd1.threePointsMade max_paniers, g.dateGame date date
FROM GAMEDETAIL gd1 
JOIN GAME g ON g.id = gd.idGame
GROUP BY g.dateGame
HAVING gd.threePointsMade >= ALL(
    SELECT MAX(gd.threePointsMade)
    JOIN GAME g ON gd.idGame = g.id
    WHERE Extract(YEAR FROM g.dateGame) = 2012
    GROUP BY g.dateGame;
)