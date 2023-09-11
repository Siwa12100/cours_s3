#ifndef def_bibliArbres
#define def_bibliArbres

#include <stdlib.h>
#include <stdio.h>

typedef struct noeud {

    int val;
    struct noeud * fg;
    struct noeud * fd;
} Noeud;
typedef Noeud * ArbreBin;

typedef enum booleen {
    FAUX, VRAI
} Booleen;

ArbreBin creerArbreVide(void);
Booleen arbreEstVide(ArbreBin b);
ArbreBin creerArbreEnracine(int val, ArbreBin sag, ArbreBin sad);
int tailleArbre(ArbreBin a);
int hauteurArbre(ArbreBin a);
void viderArbre(ArbreBin * pta);
void afficherCouche(ArbreBin a);
Booleen rechercher(ArbreBin a, int val);

// Fonctions pour arbres binaires de recherche
typedef ArbreBin Abr;
Noeud * creerNoeud(int val);
void insererEnFeuille(Abr * pta, int val);
#endif
