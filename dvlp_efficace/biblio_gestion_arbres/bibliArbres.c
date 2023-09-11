#include "bibliArbres.h"

ArbreBin creerArbreVide(void) {
    return NULL;
} // On renvoie un pointeur sur un noeud vide 

Booleen arbreEstVide(ArbreBin a) {
    if (a == NULL) return 1;
    return 0;
}

ArbreBin creerArbreEnracine( int val, ArbreBin sag, ArbreBin sad) {

    ArbreBin tmp = (ArbreBin)malloc(sizeof(ArbreBin));
    if (tmp == NULL){
        printf("\n [Erreur bibliArbres] : Soucis d'allocation memoire ! \n");
        exit(1);
    }

    tmp -> val = val;
    tmp -> fg = sag;
    tmp -> fd = sad;
    return tmp;
}

int tailleArbre(ArbreBin a) {

    if (a == NULL) return 0;
    return 1 + tailleArbre(a -> fg) + tailleArbre(a -> fd);
    // On renvoie 1 pour le noeud actuel, et la somme des autres branches 
}

int hauteurArbre(ArbreBin a) {

    if (a == NULL) return -1;
    
    int hauteurGauche = hauteurArbre(a -> fg);
    int hauteurDroite = hauteurArbre(a -> fd);

    if (hauteurGauche < hauteurDroite) return 1 + hauteurDroite;
    return 1 + hauteurGauche;
    // On renvoie 1 pour l'étage actuelle + l'hauteur la plus haute des 2 feuilles en dessous
}

void viderArbre(ArbreBin * pta) {

    if (*pta == NULL) return;
    viderArbre(&(*pta) -> fg);
    viderArbre(&(*pta) -> fd);

    free(*pta);
    *pta = NULL;
}

void afficherNtab(int val) {
    for (int i = 0; i < val; i++){
        printf("\t");
    }
}

void afficherCoucheRec(ArbreBin a, int retrait) {

    if (a -> fd != NULL){
        afficherCoucheRec(a -> fd, retrait + 1);
        afficherNtab(retrait);
        printf("\t/ \n");
    }

    afficherNtab(retrait);
    printf("%d \n", a -> val);

    if (a -> fg != NULL){
        afficherNtab(retrait);
        printf("\t\\ \n");
        afficherCoucheRec(a -> fg, retrait + 1);
    }
}

void afficherCouche(ArbreBin a) {
    if (a != NULL) afficherCoucheRec(a, 0);
}

Booleen rechercher(ArbreBin a, int val) {

    Booleen rep = 0;
    // Si l'arbre est vide, on renvoie faux 
    if (a == NULL)  return 0;

    // Si la valeur est sur le noeud actuel, on renvoie vrai 
    if (a -> val == val) return 1;
    // On recherche la valeur dans la sous branche droite 
    rep = rechercher(a -> fd, val);
    // Si on l'a trouvé, on renvoie vrai 
    if (rep == 1) return 1;

    // Si on l'a pas dans la sous branche droite, on renvoie le résultat 
    // de la sous branche gauche quel qu'il soit...
    return rechercher(a -> fg, a -> val);
}

Noeud * creerNoeud(int val) {

    ArbreBin tmp = (ArbreBin)malloc(sizeof(ArbreBin));
    if (tmp == NULL){
        printf("\n [Erreur bibliArbres] : Soucis d'allocation memoire ! \n");
        exit(1);
    }

    tmp -> fg = NULL;
    tmp -> fd = NULL;
    tmp -> val = val;
}

void insererEnFeuille(Abr * pta, int val) {

    // Si la feuille est vide, on la créée et on y met val...
    if (*pta == NULL){
            *pta = creerNoeud(val);
    }
    else if(val <= (*pta) -> val){
        insererEnFeuille(&(*pta) -> fg, val);
    }
    else{
        insererEnFeuille(&(*pta) -> fd, val);
    }
}
