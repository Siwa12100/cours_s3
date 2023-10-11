#include "avl.h"
#include <stdio.h>
#include <stdlib.h>


int lancementTestsAvl();
// Fonctions de test avl : 
// -----------------------
int testCreerNoeud();
int testCreerArbreVide();
int testEstArbreVide();
int testInsererEnFeuille();
int testViderArbre();
int testAfficherCroissantEtDecroissant();

int lancementTestsAvl(void){

    if (testCreerNoeud() != 0){
        printf("[Tests] : Erreur dans le test de création d'un noeud.\n");
        return 1;
    }

    if (testCreerArbreVide() != 0){
        printf("[Tests] : Erreur dans le test de création d'un arbre vide.\n");
        return 1;
    }

    if (testEstArbreVide() != 0){
        printf("[Tests] : Erreur dans le test de vérification d'arbre vide.\n");
        return 1;
    }

    if (testInsererEnFeuille() != 0){
        printf("[Tests] : Erreur dans l'insertion en feuille.\n"); 
        return 1;
    }

    if (testViderArbre() != 0){
        printf("[Tests] : Erreur dans le test de vidage de l'arbre.\n");
        return 1;
    }

    if (testAfficherCroissantEtDecroissant() != 0){
        printf("[Tests] : Erreur dans le test de fonctions d'affichage.\n");
        return 1;
    }
    

    //afficherCouche(a);
    return 0;
}

int testViderArbre(void) {

    Avl a = creerArbreVide();

    for (int i = 0; i < 8; i++){
        insererEnFeuille(&a, i * 3);
    }

    //afficherCroissant(a);
    viderArbre(&a);
    if (a != NULL) return 1;

    //afficherCroissant(a);
    
    return 0;
}

int testCreerNoeud(void) {

    Noeud * n = creerNoeud(66); 

    if (n == NULL || n -> val != 66) return 1;
    
    return 0;
}

int testCreerArbreVide(void) {

    Avl a = creerArbreVide();
    if (a != NULL) return 1;
    return 0;
}

int testEstArbreVide(void) {

    Avl  a = creerArbreVide(); 

    if (estArbreVide(a) != VRAI) return 1;
    return 0;
}

int testInsererEnFeuille(void) {

    Avl a = creerArbreVide();
    insererEnFeuille(&a, 118712);

    if (estArbreVide(a) != FAUX) return 1;
    if (a -> val != 118712) return 1;
    
    return 0;
}

int testAfficherCroissantEtDecroissant(void) {

    Avl a = creerArbreVide();

    for (int i = 0; i < 13; i++){

        if (i%2 == 0){
            insererEnFeuille(&a, -i * i);
        }
        else
        {
            insererEnFeuille(&a, i * i);
        }
    }
        

    afficherCroissant(a);
    afficherDecroissant(a);
    afficherCouche(a);
    return 0;
}





// ================= Fonction main =====================
int main(void) {

    if (lancementTestsAvl() != 0){
        printf("[Tests] : erreur dans l'exécution des tests !\n");
    }
    else {
        printf("[Tests] : Tous les tests unitaires effectués avec succès !\n");
    }

    return 0;
}

