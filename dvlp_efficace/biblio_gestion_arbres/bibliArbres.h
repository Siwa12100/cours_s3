#ifndef def_bibliArbres
#define def_bibliArbres

#include <stdlib.h>
#include <stdio.h>

typedef struct noeud {

    Int val;
    Noeud * fg;
    Noeud * f;
} Noeud;
typedef Noeud * ArbreBin;

ArbreBin creerArbreVide(void);
Booleen arbreEstVide(ArbreBin b);
ArbreBin creerArbreEnracine(int val, ArbreBin sag, ArbreBin sad);
int tailleArbre(ArbreBin a);
int hauteurArbre(ArbreBin a);
void viderArbre(ArbreBin * pta);
void afficherCouche(ArbreBin a);

typedef struct booleen {

    FAUX, VRAI
} Booleen;

Booleen rechercher(ArbreBin a, int val);

#endif
