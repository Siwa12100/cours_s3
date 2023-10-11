#include "avl.h"
#include <stdio.h>
#include <stdlib.h>


void mettreAjourHauteur(Noeud * ptn) {

    int hg, hd;

    hg = (ptn -> fg == NULL)? -1 : ptn -> fg -> h;
    hd = (ptn -> fd == NULL)? -1 : ptn -> fd -> h;

    ptn -> h = (hg>hd)? 1 + hg : 1 + hd;
}

ArbreBin creerArbreVide(void) {
    return NULL;
}

Booleen estArbreVide(ArbreBin b) {
    if (b == NULL) return VRAI;
    return FAUX;
}

Noeud * creerNoeud(int val) {
    Noeud * tmp = (Noeud*) malloc (sizeof(Noeud));
    if (tmp == NULL){
        printf("[infos] : Erreur d'allocation mémoire à la création d'un noeud.\n");
        exit(1);
    }

    tmp -> val = val;
    tmp -> h = 0;
    tmp -> fg = creerArbreVide(); 
    tmp -> fd = creerArbreVide();
    return tmp;
}

void insererEnFeuille(Avl * ptv, int val) {

    if (*ptv == NULL){
        *ptv = creerNoeud(val);
        return;
    }

    if ((*ptv) -> val <= val){
        insererEnFeuille(&(*ptv) -> fg, val);
        return;
    }

    insererEnFeuille(&(*ptv) -> fd, val);
}

void viderArbre(ArbreBin * ptv) {

    if (*ptv == NULL) return;
    if ((*ptv) -> fg != NULL) viderArbre(&(*ptv) -> fg);
    if ((*ptv) -> fd != NULL) viderArbre(&(*ptv) -> fd); 

    free(*ptv); 
    *ptv = NULL;
}

void parcoursAffichageCroissant(Avl v) {
    // Si le noeud actuel est nul, alors on part...
    if (v == NULL) return;
    // On affiche toutes les valeurs à gauche 
    parcoursAffichageCroissant(v -> fg);
    // On affiche la valeur du noeud actuel
    if (v -> val < 0) printf("     - (%d) \n", v -> val);     
    else printf("     - %d \n", v -> val); 
    // On affiche toutes les valeurs à droite 
   parcoursAffichageCroissant(v -> fd);
}

void afficherCroissant(Avl v) {
    printf(" \n Affichage croissant de l'arbre binaire de recherche : \n");
    printf(   " -----------------------------------------------------\n\n");
    parcoursAffichageCroissant(v);
    printf("\n");
}

void parcoursAffichageDecroissant(Avl v) {
    if (v == NULL ) return;
    parcoursAffichageDecroissant(v -> fd);
    // On affiche la valeur du noeud actuel
    if (v -> val < 0) printf("     - (%d) \n", v -> val);     
    else printf("     - %d \n", v -> val);     
    parcoursAffichageDecroissant(v -> fg);
}

void afficherDecroissant(Avl v) {
    printf(" \n Affichage decroissant de l'arbre binaire de recherche : \n");
    printf(   " -------------------------------------------------------\n\n");
    parcoursAffichageDecroissant(v);
    printf("\n");
}

// void rotationDroite(Avl * ptv){
//     // On déclare une variable allant devenir la nouvelle racine 
//     // de l'arbre. 
//     // Dans la rotation à droite, la nouvelle racine va devenir 
//     // la feuille gauche actuelle qui va donc remonter d'un cran
//     Noeud * racine = (*ptv) -> fg;
//     // Le sous arbre contenant les valeurs supérieures à celles de 
//     // la feuille gauche initiale vont être déplacées pour devenir 
//     // le sous arbre contenant les valeurs supérieures à la nouvelle racine, mais 
//     // inférieures à l'ancienne racine (donc ça va devenir le sous arbre gauche du 
//     // sous arbre droit)
//     (*ptv) -> fg = racine -> fd;
//     // Donénavant la feuille droite de la racine devient la racine itiale, qui 
//     // donc était supérieure à la valeur de la nouvelle racine 
//     racine -> fd = (*ptv);
//     // Ptv, qui est le pointeur passé en paramètre de base, prend la valeur de la 
//     // nouvelle racine 
//     *ptv = racine; 

//     // On met à jour la hauteur de la feuille droite qui vient de récupérer une
//     // nouvelle branche gauche
//     mettreAjourHauteur($(*ptv) -> fd);    
//     // On met à jour de la racine dont les deux feuilles viennent d'être
//     // modifiées
//     mettreAjourHauteur($(*ptv));
// }

// void rotationGauche(Avl * ptv) {
//     // On déclare un noeud qui va devenir la nouvelle racine 
//     Noeud * racine = (*ptv) -> fd;
    
//     // La racine initiale va devenir la feuille gauche de la nouvelle racine 
//     racine -> fg = (*ptv);

//     // Le sous arbre qui contenait les valeurs supérieures à la racine initiale,
//     // mais avec des valeurs inférieures à la feuille droite, va maintenant devenir 
//     // le sous arbre droit de la feuille gauche, pour contenir les valeurs inférieures à la racine 
//     // mais supérieures à la feuille gauche de la racine 
//     racine -> fg -> fd = (*ptv) -> fg;

//     // La racine initiale passée en paramètres devient la nouvelle racine
//     (*ptv) = racine;

//     // On met à jour la hauteur de la nouvelle racine
//     mettreAjourHauteur((*ptv));
//     // On met à jour la hauteur du sous arbre gauche partant de la racine 
//     mettreAjourHauteur(&(*ptv) -> fg)
// }