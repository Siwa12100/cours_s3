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
/* 
Dans la sous requête, on commence par récupérer le nombre maximal de paniers à 3 points 
réalisés dans les parties en 2012. 
Ensuite dans la requête principale, on récupère le max de cette valeur là, pour bien avoir 
le nombre de paniers à 3 points le plus grand réalisé pendant 2012.  
*/
-- SELECT MAX(max_paniers) AS max_paniers_saison_2012
-- FROM (
--     SELECT MAX(gd.threePointsMade) AS max_paniers
--     FROM GAMEDETAIL gd
--     JOIN GAME g ON gd.idGame = g.id
--     WHERE Extract(YEAR FROM g.dateGame) = 2012
--     GROUP BY g.dateGame
-- ) AS max_paniers_par_date;


/* Question 11 : 
---------------- */
-- Equipe la plus jeune pour la conférence de l'est 
-- SELECT t.city as ville, t.nickname as nom, t.conference, t.yearFounded
-- FROM Team t
-- WHERE t.yearFounded = (SELECT MAX(t1.yearFounded) FROM Team t1 WHERE t1.conference = 'E' GROUP BY t1.conference)
-- AND t.conference = 'E'
-- GROUP BY t.city, t.nickname, t.conference, t.yearFounded;

-- -- Equipe la plus jeune pour la conférence de l'ouest 
-- SELECT t.city as ville, t.nickname as nom, t.conference, t.yearFounded
-- FROM Team t
-- WHERE t.yearFounded = (SELECT MAX(t1.yearFounded) FROM Team t1 WHERE t1.conference = 'W' GROUP BY t1.conference)
-- AND t.conference = 'W'
-- GROUP BY t.city, t.nickname, t.conference, t.yearFounded;


/* Question 12 : 
---------------- */ 
-- SELECT p.name as nom, gd.assists as passes_decisives 
-- FROM GameDetail gd
-- JOIN Player p ON p.id = gd.idPlayer
-- JOIN Game g ON g.id = gd.idGame
-- WHERE gd.assists = (SELECT MAX(gd1.assists) FROM GameDetail gd1)
-- GROUP BY p.name, gd.assists;


/* Question 13 :
---------------- */
-- SELECT p.name AS nom_joueur,g.dateGame AS date_performance, gd.playingTime AS temps_de_jeu, gd.personnalFoul AS personnum, g.dateGame AS date_de_la_partie
-- FROM GameDetail gd
-- JOIN Player p ON gd.idPlayer = p.id
-- JOIN Game g ON gd.idGame = g.id
-- WHERE gd.personnalFoul = 6
-- ORDER BY gd.playingTime
-- LIMIT 1;


/* Question 14 : 
---------------- */ 
-- SELECT
--     home_team.nickname AS equipe_domicile,
--     visitor_team.nickname AS equipe_visiteur,
--     g.dateGame AS date_de_la_partie
-- FROM GameDetail gd
-- JOIN Game g ON gd.idGame = g.id
-- JOIN Team home_team ON g.idHomeTeam = home_team.id
-- JOIN Team visitor_team ON g.idVisitorTeam = visitor_team.id
-- WHERE gd.personnalFoul = 6
-- ORDER BY gd.playingTime
-- LIMIT 1;


/* Question 15 : 
---------------- */
SELECT p.name, p.id, gd.rebounds as rebonds, gd.assists as passes,
 gd.steals as interceptions, gd.blockedShots as contres, gd.points as points
FROM GameDetail gd
JOIN Player p ON p.id = gd.idPlayer
WHERE (gd.points >= 10 AND gd.rebounds >= 10 AND gd.assists >=10)
OR (gd.points >= 10 AND gd.rebounds >= 10 AND gd.blockedShots >= 10)
OR ( gd.points >= 10 AND gd.rebounds >= 10 AND gd.steals >= 10)
OR ( gd.points >= 10 AND gd.assists >= 10 AND gd.blockedShots >= 10)
OR ( gd.points >= 10 AND gd.assists >= 10 AND gd.steals >= 10)
OR ( gd.points >= 10 AND gd.blockedShots >= 10 AND gd.steals >= 10)
OR ( gd.rebounds >= 10 AND gd. blockedShots >= 10 AND gd.assists >= 10)
OR ( gd.rebounds >= 10 AND gd.assists >= 10 AND gd.steals >= 10)
OR ( gd.rebounds >= 10 AND gd.blockedShots >= 10 AND gd.steals >= 10)
OR ( gd.assists >= 10 AND gd.blockedShots >= 10 AND gd.steals >= 10);


/* Question 16 :
---------------- */ 
-- SELECT p.name, gd.steals as balles_interceptees,
--          gd.turnovers as balles_perdues
-- FROM GameDetail gd 
-- JOIN Game g ON g.id = gd.idGame
-- JOIN Player p ON p.id = gd.idPlayer
-- WHERE gd.steals > gd.turnovers
-- AND gd.steals >= 1001;

-- SELECT p.id, p.name, SUM(gd.steals) as somme_des_interceptions, 
--         SUM(gd.turnovers) as somme_des_pertes_de_balles
-- FROM GameDetail gd 
-- JOIN Player p ON p.id = gd.idPlayer
-- GROUP BY p.id, p.name
-- HAVING SUM(gd.turnovers) < SUM(gd.steals) 
-- AND SUM(gd.steals) >= 1000;
-- ...
