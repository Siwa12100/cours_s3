#ifndef RESEAU_H
#define RESEAU_H
#include "codeRetour.h"


typedef struct CellSommet{

    int id;
    struct CellSommet * suiv;
    struct CellArc * listeConnexions;
}Ordi;

typedef struct CellArc{

    Ordi * extremite;
    struct CellArc * suivant;
}Connexion;

typedef enum booleen {
    FAUX, /**< Valeur représentant faux. */
    VRAI /**< Valeur représentant vrai. */
} Booleen;

typedef Ordi * Reseau;

Reseau creerReseauVide();
Booleen estReseauVide();
void affichageReseau(Reseau r);
Ordi * rechercherOrdiPt(Reseau r, int id);
CodeRetour ajouterOrdi(Reseau * r, int id);
CodeRetour rechercherConnexion(Reseau r, int dep, int arr);
CodeRetour ajouterConnexion(Reseau * ptr, int idDep, int idArr);

#endif
