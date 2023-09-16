#include "abr.h"
#include <stdio.h>
#include <stdlib.h>

ArbreBin creerArbreVide(void) {
    return NULL;
}

Booleen estArbreVide(ArbreBin b) {
    if (b == NULL) return 1; 
    return 0; 
}

void insererEnFeuille(Abr * pta, int val) {
    // Si l'arbre est vide, on créé un noeud et on y met val 
    if ( * pta == NULL){
        * pta = creerNoeud(val);
        return;
    }
    // Si la valeur est <= à celle du noeud, on insère à gauche 
    if (val <= (*pta) -> val){
        insererEnFeuille(&(*pta) -> fg, val);
        return;
    }
    // Sinon, elle val est > à celle du noeud donc on insère à droite  
    insererEnFeuille(&(*pta) -> fd, val);
}

Noeud * creerNoeud(int val) {

    Noeud * tmp = (Noeud *) malloc (sizeof(Noeud));
    if (tmp == 0){
        printf("[infos]: Erreur d'allocation mémoire à la création d'un noeud.");
        exit(1);
    }

    tmp -> fd = creerArbreVide();
    tmp -> fg = creerArbreVide(); 
    tmp -> val = val; 
    return tmp;
}