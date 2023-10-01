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
    // Pour l'exo 2 :
    tmp -> h = 0;
    return tmp;
}

void viderArbre(ArbreBin * pta) {

    if (*pta == NULL) return; 
    if ((*pta) -> fd != NULL) viderArbre(&(*pta) -> fd); 
    if ((*pta) -> fg != NULL) viderArbre(&(*pta) -> fg);

    free(*pta); 
    * pta = NULL;
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
    printf("\n");
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
    // Mise à jour de l'affichage pour l'exo  2 (ajout de la hauteur...)
    printf("%d (h : %d)\n", a -> val, a -> h);

    if (a -> fg != NULL){
        afficherNtab(retrait);
        printf("\t\\ \n");
        afficherCoucheRec(a -> fg, retrait + 1);
    }
}

void afficherCouche(ArbreBin a) {
    printf("\n Affichage de l'arbre en graphique : \n");
    printf(  " -----------------------------------\n\n");
    if (a != NULL) afficherCoucheRec(a, 0);
    printf("\n\n");
}

int oterMax(Abr * pta){
    // Si la feuille droite suivante est nulle, on est au bout de la partie droite de l'arbre 
    if ((*pta) -> fd == NULL){
        // On récupère donc la valeur du noeud actuel (la plus grande du sous arbre gauche)
        int val = (*pta) -> val;
        // On créé un noeud temporaire pour supprimer le noeud actuel 
        Noeud * tmp = *pta;
        // On dirige la feuille droite du noeud précédent vers la feuille gauche actuelle (car c'est la seule qui reste après)
        *pta = (*pta) -> fg;
        // On supprime le noeud actuel 
        free(tmp);
        // On retourne la valeur 
        return val;
    }
    // Sinon, ça veut dire qu'il reste des valeurs à droite, alors on va retourner la valeur à droite 
    return oterMax(&(*pta) -> fd);
}

Booleen supprimerVal(Abr * pta, int val) {
    // Si le noeud actuel est nul, on ne peut rien supprimer, on part en renvoyant faux 
    if (*pta == NULL) return 0;
    // Si la valeur à supprimer est égale à celle du noeud actuel, alors on la supprime
    if ((*pta) -> val == val){
        // On créé un noeud temporaire pour stocker le noeud actuel que l'on va supprimer une fois les liaisons refaites 
        Noeud * tmp = * pta;
        // Si la feuille droite est nulle 
        if ((*pta) -> fd == NULL){
            // Alors on redirige directement vers la feuille gauche 
            *pta = (*pta) -> fg;
            // On supprime le noeud actuel 
            free(tmp);
        }
        // Si la feuille droite n'est donc pas nulle mais que la feuille gauche si 
        else if ((*pta) -> fg == NULL){
            // On redirige donc vers la feuille droite (puisqu'elle n'est pas nulle)
            *pta = (*pta) -> fd;
            // On supprime le noeud actuel 
            free(tmp);
        }
        //Sinon, on est dans le cas où ni la feuille gauche ou droite ne sont nulles 
        else{
            // On va donner au noeud actuel la valeur plus grande valeur inférieure à celle du noeud actuel 
            // Il faut que cette valeur soit à la fois plus grande que toutes celles de la feuille gauche
            // Tout en étant toujours plus petite que la valeur de la feuille droite pour rester les règles de l'arbre 
            // On va donc la charger dans la feuille la plus à droite de l'arbre gauche, cad la valeur la plus grande parmis 
            // les plus petites que la valeur du noeud actuel 
            (*pta) -> val = oterMax(&(*pta) -> fg);
        }

        return 1;
    }
    // Si la valeur n'est pas dans le noeud actuel, et qu'elle est égale ou plus petite que celle du noeud actuel 
    // On va supprimer à gauche (et on retourne la valeur)
    if ((*pta) -> val >= val) return supprimerVal(&(*pta) -> fg, val);
    // Sinon, on va supprimer à droite et on retourne la valeur 
    return  supprimerVal(&(*pta) -> fd, val);
}

Booleen rechercherVal(Abr a, int val) {
    // Si le noeud est nul, la valeur n'y est pas, on part et on retourne faux
    if (a == NULL) return 0;
    // Si la valeur est dans le noeud actuel, on part et on retourne vrai 
    if (a -> val == val) return 1;
    // Si la valeur est inférieure à celle du noeud actuel, on part à gauche 
    if (a -> val > val) return rechercherVal(a -> fg, val);
    // Si la valeur est supérieure à celle du noeud actuel, on part à droite 
    if (a -> val < val) return rechercherVal(a -> fd, val);

    return 0;
}
