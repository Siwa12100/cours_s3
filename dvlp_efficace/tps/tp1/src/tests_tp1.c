#include "abr.h"
#include <stdio.h>
#include <stdlib.h>

int lancementTests();
int test_creerArbreVide();
int testEstArbreVide();

int main(void) {
    
    int a = lancementTests();
    
    return 0;
}

int lancementTests() {

    if (test_creerArbreVide() != 0){
        printf("[infos] : Erreur dans le test de creerArbreVide.\n");
        return 1;
    }

    if (testEstArbreVide() != 0){
        printf("[infos] : Erreur dans le test unitaire de estArbreVide.\n ");
        return 1;
    }

    printf("[Infos]  : Tests unitaires exécutés avec succès ! \n");
    return 0;
}

int test_creerArbreVide(void) {

    ArbreBin b = creerArbreVide();
    if (b != NULL) return 1;
    return 0;
}

int testEstArbreVide(void) {
    ArbreBin b = creerArbreVide();
    Booleen verif = estArbreVide(b);
    
    if (verif != VRAI) return 1;
    return 0; 
}