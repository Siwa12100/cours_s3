#include "reseau.h"
#include <stdio.h>
#include <stdlib.h>


int lancementTests();
int testCreerReseauVide();
int testEstReseauVide();
int testAjouterOrdi();
Reseau genererReseau(int nb);
int testAffichageReseau();
int testRechercherOrdi();


int main(void) {
    printf("\n");
    int v = lancementTests();
    printf("\n");
    return v;
}

int lancementTests(void) {

    if (testCreerReseauVide() != 0){
        printf("[tests] : Echec du test de creerReseauVide. \n");
        return 1;
    }

    if (testEstReseauVide() != 0){
        printf("[tests] : Echec du test de estReseauVide. \n");
        return 1;
    }

    if (testAjouterOrdi() != 0){
        printf("[tests] : Echec du test d'ajout d'un ordi.\n");
        return 1;
    }

    //testAffichageReseau();

    if (testRechercherOrdi() != 0){
        printf("[tests] : Echec du test de recherche d'un ordi.\n");
        return 1;
    }

    printf("[tests] : Tous les tests unitaires bien effectués.\n");
    return 0;
}

int testCreerReseauVide(void) {
    Reseau r = creerReseauVide();
    if (r != NULL) return 1;
    return 0;
}

int testEstReseauVide(void) {
    Reseau r = creerReseauVide();
    Booleen b = estReseauVide(r);

    if (b != VRAI) return 1;
    return 0;
}

Reseau genererReseau(int nb) {

    Reseau r = creerReseauVide();

    for (int i = 1; i <= nb; i++){
        ajouterOrdi(&r, i);
    }

    return r;
}

int testAjouterOrdi(void) {

    // ajoute 7 ordis au réseau...
    Reseau r = genererReseau(8);
    Ordi * tmp = r;
    int val = 0;

    while (tmp != NULL){
        //printf(" %d ; ", tmp -> id);
        tmp = tmp -> suiv;
        val = val + 1;
    }

    //printf("\n val : %d", val);
    if (val != 8) return 1;
    //printf("\n");
    return 0;
}

int testAffichageReseau(void) {

    Reseau r = genererReseau(7);
    affichageReseau(r);

    return 0;
}

int testRechercherOrdi(void) {

    Reseau r = creerReseauVide();
    ajouterOrdi(&r, 35); 

    Ordi * tmp = rechercherOrdiPt(r, 35);
    if (tmp == NULL) return 1;
    return 0;
}