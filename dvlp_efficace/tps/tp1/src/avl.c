#include "avl.h"
#include <stdio.h>
#include <stdlib.h>


int parcoursHauteur(Avl * v) {
    // Si le noeud est nul, on met sa hauteur à (-1) et on part 
    if ((*v) == NULL){
        (*v) -> h = (-1);
        // On renvoie la hauteur du noeud + 1 pour lui
        return (*v) -> h + 1;
    }
    printf("\n\n\n [mise a jour hauteur] Passage après le premier if \n\n\n");
    // S'il n'est pas nul mais que ses deux feuilles sont nulles, 
    // on met sa hauteur à 0 
    if (&(*v) -> fd == NULL && &(*v) -> fg  == NULL){
        (*v) -> h = 0;
        // On renvoie la hauteur du noeud + 1 pour lui 
        return (*v) -> h + 1;
    }

    printf("\n\n\n [Mise a jour hauteur] : Passage après les premiers if...\n\n\n");
    // On va stocker la hauteur de l'arbre droit et gauche 
    int hg = parcoursHauteur(&(*v) -> fg);
    int hd = parcoursHauteur(&(*v) -> fd);
    printf("[Mise a jour hauteur] : Passage après maj hd & hg \n\n\n");
    if (hd <= hg){
        // La hauteur du noeud est celle de la feuille gauche 
        (*v) -> h = hg;
        // On renvoie cette hauteur + 1 pour compter le noeud actuel
        return hg + 1;
    }
    // Sinon, la hauteur du noeud est celle de la feuille droite
    (*v) -> h = hd + 1;
    // On renvoie la hauteur du noeud actuel + 1 pour prendre en compte sa hauteur
    return hd + 1;
}

void mettreAjourHauteur(Avl * v) {
    (*v) -> h = parcoursHauteur(v);
}
