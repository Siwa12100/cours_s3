/* Question 1 :
--------------- */ 
-- Pas besoin de faire encore apparemment....

/* Question 2 :
-------------- */

-- EXPLAIN ANALYZE
--     SELECT p.name , t1.abbreviation , t2.abbreviation , g.dateGame
--     FROM Player p, Team t1, Team t2, GameDetail gd, Game g
--     WHERE p.id = gd.idPlayer AND g.id = gd.idGame AND t1.id = gd.idTeam
--     AND ((g.idHomeTeam = t1.id AND g.idVisitorTeam = t2.id)
--     OR (g.idVisitorTeam = t1.id AND g.idHomeTeam = t2.id))
--     AND gd.personnalFoul > 6;


    -- Resultat : 
    -------------

                                                                                            --QUERY PLAN                                                                                        
     
-- ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- -----
--  Nested Loop  (cost=1001.37..16949.67 rows=1 width=49) (actual time=74.281..76.706 rows=1 loops=1)
--    Join Filter: ((((g.idhometeam)::text = (t1.id)::text) AND ((g.idvisitorteam)::text = (t2.id)::text)) OR (((g.idvisitorteam)::text = (t1.id)::text) AND ((g.idhometeam)::text = (t2.id)::tex
-- t)))
--    Rows Removed by Join Filter: 1
--    ->  Nested Loop  (cost=1000.97..16941.45 rows=1 width=93) (actual time=74.269..76.692 rows=1 loops=1)
--          Join Filter: ((gd.idteam)::text = (t1.id)::text)
--          ->  Nested Loop  (cost=1000.57..16934.66 rows=1 width=50) (actual time=74.238..76.659 rows=1 loops=1)
--                ->  Nested Loop  (cost=1000.28..16926.35 rows=1 width=33) (actual
--  time=74.210..76.631 rows=1 loops=1)
--                      ->  Gather  (cost=1000.00..16918.05 rows=1 width=26) (actual time=74.164..76.583 rows=1 loops=1)
--                            Workers Planned: 2
--                            Workers Launched: 2
--                            ->  Parallel Seq Scan on gamedetail gd  (cost=0.00..15917.95 rows=1 width=26) (actual time=56.276..69.193 rows=0 loops=3)
--                                  Filter: (personnalfoul > '6'::numeric)
--                                  Rows Removed by Filter: 215221
--                      ->  Index Scan using player_pkey on player p  (cost=0.28..8.30 rows=1 width=19) (actual time=0.042..0.042 rows=1 loops=1)
--                            Index Cond: ((id)::text = (gd.idplayer)::text)
--                ->  Index Scan using game_pkey on game g  (cost=0.29..8.30 rows=1 width=35) (actual time=0.026..0.026 rows=1 loops=1)
--                      Index Cond: (id = gd.idgame)
--          ->  Bitmap Heap Scan on team t1  (cost=0.40..4.42 rows=190 width=54) (actual time=0.027..0.028 rows=1 loops=1)
--                Recheck Cond: (((g.idhometeam)::text = (id)::text) OR ((g.idvisitorteam)::text = (id)::text))
--                Heap Blocks: exact=1
--                ->  BitmapOr  (cost=0.40..0.40 rows=2 width=0) (actual time=0.018..0.019 rows=0 loops=1)
--                      ->  Bitmap Index Scan on team_pkey  (cost=0.00..0.15 rows=1 width=0) (actual time=0.014..0.014 rows=1 loops=1)
--                            Index Cond: ((id)::text = (g.idhometeam)::text)
--                      ->  Bitmap Index Scan on team_pkey  (cost=0.00..0.15 rows=1 width=0) (actual time=0.002..0.002 rows=1 loops=1)
--                            Index Cond: ((id)::text = (g.idvisitorteam)::text)
--    ->  Bitmap Heap Scan on team t2  (cost=0.40..4.42 rows=190 width=54) (actual time=0.008..0.009 rows=2 loops=1)
--          Recheck Cond: (((g.idvisitorteam)::text = (id)::text) OR ((g.idhometeam)::text = (id)::text))
--          Heap Blocks: exact=1
--          ->  BitmapOr  (cost=0.40..0.40 rows=2 width=0) (actual time=0.007..0.007 rows=0 loops=1)
--                ->  Bitmap Index Scan on team_pkey  (cost=0.00..0.15 rows=1 width=0) (actual time=0.002..0.002 rows=1 loops=1)
--                      Index Cond: ((id)::text = (g.idvisitorteam)::text)
--                ->  Bitmap Index Scan on team_pkey  (cost=0.00..0.15 rows=1 width=0) (actual time=0.001..0.002 rows=1 loops=1)
--                      Index Cond: ((id)::text = (g.idhometeam)::text)
--  Planning Time: 4.410 ms
--  Execution Time: 76.913 ms


/* Question 3 :
--------------- */

-- Création d'un index sur la colonne personnalFoul de la colonne Gamedetails 
-- CREATE INDEX idx_gdPersonnalFouls ON GameDetail(personnalFoul);

-- EXPLAIN ANALYZE
--     SELECT p.name , t1.abbreviation , t2.abbreviation , g.dateGame
--     FROM Player p, Team t1, Team t2, GameDetail gd, Game g
--     WHERE p.id = gd.idPlayer AND g.id = gd.idGame AND t1.id = gd.idTeam
--     AND ((g.idHomeTeam = t1.id AND g.idVisitorTeam = t2.id)
--     OR (g.idVisitorTeam = t1.id AND g.idHomeTeam = t2.id))
--     AND gd.personnalFoul > 6;


    
    -- Résultat : 
    -------------
--                                                                                             QUERY PLAN                                                                                             
-- ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--  Nested Loop  (cost=1.79..40.07 rows=1 width=49) (actual time=0.078..0.083 rows=1 loops=1)
--    Join Filter: ((((g.idhometeam)::text = (t1.id)::text) AND ((g.idvisitorteam)::text = (t2.id)::text)) OR (((g.idvisitorteam)::text = (t1.id)::text) AND ((g.idhometeam)::text = (t2.id)::text)))
--    Rows Removed by Join Filter: 1
--    ->  Nested Loop  (cost=1.39..31.85 rows=1 width=93) (actual time=0.064..0.067 rows=1 loops=1)
--          Join Filter: ((gd.idteam)::text = (t1.id)::text)
--          ->  Nested Loop  (cost=0.99..25.05 rows=1 width=50) (actual time=0.044..0.047 rows=1 loops=1)
--                ->  Nested Loop  (cost=0.71..16.75 rows=1 width=33) (actual time=0.032..0.034 rows=1 loops=1)
--                      ->  Index Scan using idx_gdpersonnalfouls on gamedetail gd  (cost=0.42..8.44 rows=1 width=26) (actual time=0.017..0.019 rows=1 loops=1)
--                            Index Cond: (personnalfoul > '6'::numeric)
--                      ->  Index Scan using player_pkey on player p  (cost=0.28..8.30 rows=1 width=19) (actual time=0.010..0.010 rows=1 loops=1)
--                            Index Cond: ((id)::text = (gd.idplayer)::text)
--                ->  Index Scan using game_pknight owl*ey on game g  (cost=0.29..8.30 rows=1 width=35) (actual time=0.010..0.010 rows=1 loops=1)
--                      Index Cond: (id = gd.idgame)
--          ->  Bitmap Heap Scan on team t1  (cost=0.40..4.42 rows=190 width=54) (actual time=0.016..0.016 rows=1 loops=1)
--                Recheck Cond: (((g.idhometeam)::text = (id)::text) OR ((g.idvisitorteam)::text = (id)::text))
--                Heap Blocks: exact=1
--                ->  BitmapOr  (cost=0.40..0.40 rows=2 width=0) (actual time=0.011..0.012 rows=0 loops=1)
--                      ->  Bitmap Index Scan on team_pkey  (cost=0.00..0.15 rows=1 width=0) (actual time=0.006..0.006 rows=1 loops=1)
--                            Index Cond: ((id)::text = (g.idhometeam)::text)
--                      ->  Bitmap Index Scan on team_pkey  (cost=0.00..0.15 rows=1 width=0) (actual time=0.003..0.004 rows=1 loops=1)
--                            Index Cond: ((id)::text = (g.idvisitorteam)::text)
--    ->  Bitmap Heap Scan on team t2  (cost=0.40..4.42 rows=190 width=54) (actual time=0.009..0.010 rows=2 loops=1)
--          Recheck Cond: (((g.idvisitorteam)::text = (id)::text) OR ((g.idhometeam)::text = (id)::text))
--          Heap Blocks: exact=1
--          ->  BitmapOr  (cost=0.40..0.40 rows=2 width=0) (actual time=0.007..0.008 rows=0 loops=1)
--                ->  Bitmap Index Scan on team_pkey  (cost=0.00..0.15 rows=1 width=0) (actual time=0.003..0.003 rows=1 loops=1)
--                      Index Cond: ((id)::text = (g.idvisitorteam)::text)
--                ->  Bitmap Index Scan on team_pkey  (cost=0.00..0.15 rows=1 width=0) (actual time=0.003..0.003 rows=1 loops=1)
--                      Index Cond: ((id)::text = (g.idhometeam)::text)
--  Planning Time: 1.455 ms
--  Execution Time: 0.160 ms



--> Le temps d'exécution est passé de 76 ms à 0,160 ms.


/* Question 4 :
--------------- */ 
    -- SELECT abs(g.ptsHome - g.ptsAway) as ecart_de_points, t.nickname as equipe
    -- FROM Game g, Team t
    -- WHERE (g.homeTeamWins = true AND t.id = g.idHomeTeam)
    -- OR (g.homeTeamWins = false AND t.id = g.idVisitorTeam)
    -- GROUP BY g.id, t.id
    -- HAVING abs(g.ptsHome - g.ptsAway) = (SELECT MAX(abs(g1.ptsHome - g1.ptsAway))
    --                                 FROM Game g1);


/* Question 5 : 
--------------- */ 
-- EXPLAIN ANALYZE 
--     SELECT abs(g.ptsHome - g.ptsAway) as ecart_de_points, t.nickname as equipe
--     FROM Game g, Team t
--     WHERE (g.homeTeamWins = true AND t.id = g.idHomeTeam)
--     OR (g.homeTeamWins = false AND t.id = g.idVisitorTeam)
--     GROUP BY g.id, t.id
--     HAVING abs(g.ptsHome - g.ptsAway) = (SELECT MAX(abs(g1.ptsHome - g1.ptsAway))
--                                     FROM Game g1);


--> Temps d'exécution 30ms 


/* Question 6 : 
---------------*/
-- DROP INDEX idx_gWinnerAndPoints IF EXISTS;
-- CREATE INDEX idx_gWinnerAndPoints ON Game(homeTeamWins, ptsAway, ptsHome);

-- EXPLAIN ANALYZE 
--     SELECT abs(g.ptsHome - g.ptsAway) as ecart_de_points, t.nickname as equipe
--     FROM Game g, Team t
--     WHERE (g.homeTeamWins = true AND t.id = g.idHomeTeam)
--     OR (g.homeTeamWins = false AND t.id = g.idVisitorTeam)
--     GROUP BY g.id, t.id
--     HAVING abs(g.ptsHome - g.ptsAway) = (SELECT MAX(abs(g1.ptsHome - g1.ptsAway))
--                                     FROM Game g1);


/* Question 7 : 
--------------- */
-- SELECT 
