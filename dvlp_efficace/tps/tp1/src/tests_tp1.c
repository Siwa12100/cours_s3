#include "abr.h"
#include <stdio.h>
#include <stdlib.h>

int lancementTests();
int test_creerArbreVide();
int testEstArbreVide();
int testCreerNoeud();
int testInsererEnFeuille(); 
int testViderArbre();
int testAfficherCroissant();
int testAfficherDecroissant();
void effacerTerminal();

int main(void) {
    effacerTerminal();
    return lancementTests();
    
}

void effacerTerminal(void) {

    #ifdef __linux__
        system("clear");
    #endif
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

    if (testCreerNoeud() != 0){
        printf("[infos] : Erreur dans le test unitaire testCreerNoeud.\n");
        return 1;
    }

    if (testInsererEnFeuille() != 0){
        printf("[infos] : Erreur dans le test unitaire d'insertion en feuille.\n"); 
        return 1;
    }

    if (testViderArbre() != 0){
        printf("[infos] : Erreur dans le test unitaire de vidage de l'arbre.\n"); 
        return 1;
    }

    // testAfficherCroissant();
    // testAfficherDecroissant();

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

int testCreerNoeud(void) {
    Noeud * n = creerNoeud(24);

    if (n -> val != 24) return 1;
    if (n -> fd != NULL || n -> fd != NULL) return 1;
    return 0;
}

int testInsererEnFeuille(void) {

    Abr a1 = creerArbreVide(); 
    Abr a2 = creerArbreVide(); 

    int val = 15; 

    insererEnFeuille(&a1, val); 
    if (a1 -> val != 15) return 1;
    if (a1 -> fg != NULL) return 1; 
    if (a1 -> fd != NULL) return 1; 

    // Pour débugguer 
    //printf("[infos] : test d'insertion dans un arbre vide réussit ! \n"); 

    a2 = creerNoeud(val);
    insererEnFeuille(&a2, val);
    insererEnFeuille(&a2, 14); 
    insererEnFeuille(&a2, 17);
    
    if (a2 -> val != val) return 1;
    if (a2 -> fd -> val != 17){
        printf("[infos] : Mauvaise insertion de valeur supérieure dans test unitaire d'insertion en feuille.\n");
        return 1; 
    }
    if (a2 -> fg -> val != 15){
        printf("[infos] : Mauvaise insertion de valeur égale dans test unitaire d'insertion en feuille.\n");
        return 1;
    }

    if (a2 -> fg -> fg -> val != 14){
        printf("[infos] : Mauvaise insertion de valeur inférieur dans le test unitaire d'insertion en feuille.\n"); 
        return 1;
    }
    // Pour le débuggage 
    //printf("[infos] : test d'insertion dans un arbre non vide réussit ! \n"); 
    
    return 0;
}

int testViderArbre(void) {

    ArbreBin a = creerArbreVide(); 
    for (int i =0; i < 10; i++){
        insererEnFeuille(&a, i * 2);
    }
    
    for (int i = 10; i > 0; i--){
        insererEnFeuille(&a, i * 2);
    }

    viderArbre(&a); 
    if (a != NULL) return 1;
    return 0;
}

int testAfficherCroissant(void){

    Abr a = creerArbreVide();
    insererEnFeuille(&a, 13);
    insererEnFeuille(&a, -524);
    insererEnFeuille(&a,26 );
    insererEnFeuille(&a, 17);
    insererEnFeuille(&a,2 );
    insererEnFeuille(&a, 8 );
    insererEnFeuille(&a, 100);
    insererEnFeuille(&a, 200);
    insererEnFeuille(&a,1 );
    insererEnFeuille(&a, 9);

    afficherCroissant(a);
    return 0;
}

int testAfficherDecroissant(void) {
    
    Abr a = creerArbreVide();
    insererEnFeuille(&a, 13);
    insererEnFeuille(&a,26 );
    insererEnFeuille(&a, 17);
    insererEnFeuille(&a,2 );
    insererEnFeuille(&a, -524);
    insererEnFeuille(&a, 8 );
    insererEnFeuille(&a, 100);
    insererEnFeuille(&a, 200);
    insererEnFeuille(&a,1 );
    insererEnFeuille(&a, 9);

    afficherDecroissant(a);
    return 0;
}