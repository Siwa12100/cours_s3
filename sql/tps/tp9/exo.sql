------------------
TP - 9 | Revisions
------------------


-- 1.)
------
Select Distinct m.espece 
From Membre m 
Join Vaisseau v on v.numero = m.affectation
Join Planete p on v.base = p.code
Where p.systeme = 'Corellien'
ORDER BY ASC;


-- 2.)
-----
SELECT v.numero, v.modele
From Vaisseau v, Transport t 
Where t.transporteur = v.numero 
GROUP BY v.numero, v.modele
Having count(*) >= ALL (Select count(*) from Transport t GROUP BY t.transporteur);


-- 3.)
-----
SELECT m.matricule, m.nom
From Membre m
-- Join Planete p on p.code = m.planeteNaiss
Join Vaisseau v ON v.numero = m.affectation 
Where v.base = m.planeteNaiss
And m.metier = 'pilote';


-- 4.)
Create Index idx1 ON Membre(metier);


-- 5.)
-----
Create Or Replace Function  capaciteEvacuation(planete Planete.code%TYPE) Returns Integer AS $$
DECLARE
    cpt Integer := 0;
    valeurCourant Integer := 0;
    curs cursor for Select mo.nbPassagersMax
                    From Vaisseau v 
                    Join Modele mo on mo.nomCode = v.numero
                    Where v.base = planete;
BEGIN

    OPEN curs;
    FETCH curs INTO valeurCourant;

    WHILE FOUND LOOP
        cpt = cpt + valeurCourant;
        FETCH curs INTO valeurCourant;
    END LOOP;

    CLOSE curs;

    Return cpt;
END;

$$ LANGUAGE plpgsql;


-- 6.)
-----
SELECT (p.population - capaciteEvacuation(p.code)
FROM Planete p 
Where p.denomination = 'Coruscent';

-- 7.)
-----
Create Or Replace Function maintenance(membre Membre.matricule%TYPE, planete Planete.code%TYPE) Returns void AS $$
DECLARE
    curs Cursor for Select v.numero 
                    From Vaisseau v
                    Where v.base = planete;
    
    apparition Integer := 0;

BEGIN

Select count(m.numero) into apparition
From membre m 
Join Vaisseau v ON v.numero = m.affectation 
Where v.base = planete;

IF apparition == 0 THEN
    RAISE no_data_found Using Message 'le pilote % est pas sur la planete % !', membre, planete
END IF;

OPEN curs;
    FETCH curs INTO valeurCourant;






END;
$$ LANGUAGE plpgsql;

-- ========= Notes ========== -- 
-- Create Or Replace Function  Returns  AS $$
-- DECLARE

-- BEGIN

-- END;
-- $$ LANGUAGE plpgsql;



