#include "abr.h"
#include "avl.h"
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
int testAfficherCouche();
int testSupprimerVal();
int testRechercherVal();
int testMettreAjourHauteur();

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
    //testAfficherCouche();

    if (testSupprimerVal() != 0){
        printf("[infos] : Erreur dans le test unitaire de la suppression de valeur.\n");
        return 1;
    }

    if (testRechercherVal() != 0){
        printf("[infos] : Erreur dans le test unitaire de recherche d'une valeur.\n");
        return 1;
    }

    if (testMettreAjourHauteur() != 0){
        printf("[infos] : Erreur dans le test unitaire de mise à jour de la hauteur.\n");
        return 1;
    }

    printf("[Infos]  : Tests unitaires exécutés avec succès ! \n");
    return 0;
}

int testMettreAjourHauteur(void) {
    Avl * v = creerArbreVide();
    insererEnFeuille(&v, 13);
    insererEnFeuille(&v, -524);
    insererEnFeuille(&v,26 );
    insererEnFeuille(&v, 17);
    insererEnFeuille(&v,2 );
    insererEnFeuille(&v, 8 );
    insererEnFeuille(&v, 100);
    insererEnFeuille(&v, 200);
    insererEnFeuille(&v,1 );
    insererEnFeuille(&v, 9);
    afficherCouche(v);
    printf("\n\n\n [temp] : Construction et affichage de l'arbre.\n\n\n");
    mettreAjourHauteur(v); // ...
    printf("\n\n\n [temp] : Passage après le mettre à jour hauteur.\n\n\n");
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

int testAfficherCouche(void) {

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

    afficherCouche(a);
    return 0;
}

int testSupprimerVal(void) {

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

    insererEnFeuille(&a, 265);
    insererEnFeuille(&a, 265);
    insererEnFeuille(&a, 265);
    insererEnFeuille(&a, 265);
    //afficherCroissant(a);

        
    if (supprimerVal(&a, 265) != 1) return 1;
    
    int cpt = 0;
    while (supprimerVal(&a, 265)){
        cpt +=1;
    }

    if (cpt != 3) return 1;
    if (supprimerVal(&a, 265)) return 1;

    afficherCroissant(a);
    
    return 0;
}

int testRechercherVal(void) {

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
    insererEnFeuille(&a, 265);

    if (rechercherVal(a, 8) != 1) return 1;
    if (rechercherVal(a, 1000)  != 0) return 1;
    return 0;
}