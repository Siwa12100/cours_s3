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

void viderArbre(ArbreBin * pta) {

    if (*pta == NULL) return; 
    if ((*pta) -> fd != NULL) viderArbre(&(*pta) -> fd); 
    if ((*pta) -> fg != NULL) viderArbre(&(*pta) -> fg);

    free(*pta); 
    * pta = NULL;
}

void recupererValeursCroissantesArbres(int * tab, int * tailleTab, Abr b) {

    // Si le noeud actuel est nul, alors on renvoie directement le tableau sans ajouts 
    if (b == NULL) return;
    
    // On récupère tous les valeurs inférieures à la valeur du noeud
    recupererValeursCroissantesArbres(tab, tailleTab, b -> fg);
    // On récupère la valeur du noeud
    printf("\n[debug] : Val avant de rentrer dans tab : %d \n", b -> val);
    int position = * tailleTab - 1;
    printf("[debug] : Position à ce moment là : %d ; taille tab : %d \n", position, *tailleTab);
    tab[position] = b -> val;
    printf("[debug] : Valeur de tab après insertion : %d \n", tab[position]);


    // On agrandi le tableau de 1 pour stocker la valeur du noeud actuel 
    tab = (int*) realloc(tab, sizeof(int) * ((*tailleTab) + 1));
    // Position prend la position dans le tableau où la valeur du noeud devra se trouver 
    * tailleTab += 1;

    // On récupère toutes les valeurs supérieures à la valeur du noeud
    recupererValeursCroissantesArbres(tab, tailleTab, b -> fd);

    // On retourne le tableau avec toutes les valeurs de fg, fd et du noeud 
    return;    
}

void parcoursAffichageCroissant(Abr b) {
    // Si le noeud actuel est nul, alors on part...
    if (b == NULL) return;
    // On affiche toutes les valeurs à gauche 
    parcoursAffichageCroissant(b -> fg);
    // On affiche la valeur du noeud actuel
    if (b -> val < 0) printf("     - (%d) \n", b -> val);     
    else printf("     - %d \n", b -> val); 
    // On affiche toutes les valeurs à droite 
   parcoursAffichageCroissant(b -> fd);
}

void afficherCroissant(Abr b) {
    printf(" \n Affichage croissant de l'arbre binaire de recherche : \n");
    printf(   " -----------------------------------------------------\n\n");
    parcoursAffichageCroissant(b); 
}

void parcoursAffichageDecroissant(Abr b) {
    if (b == NULL ) return;
    parcoursAffichageDecroissant(b -> fd);
    // On affiche la valeur du noeud actuel
    if (b -> val < 0) printf("     - (%d) \n", b -> val);     
    else printf("     - %d \n", b -> val);     
    parcoursAffichageDecroissant(b -> fg);
}

void afficherDecroissant(Abr b) {
    printf(" \n Affichage decroissant de l'arbre binaire de recherche : \n");
    printf(   " -------------------------------------------------------\n\n");
    parcoursAffichageDecroissant(b);
    printf("\n");
}
