#include "reseau.h"
#include "codeRetour.h"
#include <stdio.h>
#include <stdlib.h>


Reseau creerReseauVide(void) {
    return NULL;
}

Booleen estReseauVide(Reseau r) {
    if (r == NULL){
        return VRAI;
    }
    return FAUX;
}

void affichageReseau(Reseau r) {

    Ordi * tmpOrdi = r;
    Connexion * tempCo = r -> listeConnexions;

    printf("\n Affichage du reseau : \n");
    printf(  " ---------------------");
    
    while (tmpOrdi != NULL){
        
        printf("\n %d : ", tmpOrdi -> id);

        while (tempCo != NULL){

            printf("\n\t -> %d ", tempCo -> extremite -> id);
        }

        tmpOrdi = tmpOrdi -> suiv;
        
        if (tmpOrdi == NULL){
            printf("\n\n");
            return;
        }

        tempCo = tmpOrdi -> listeConnexions;
    }
    printf("\n\n");
}

Ordi * rechercherOrdiPt(Reseau r, int id) {

    Ordi * tmpOrdi = r;

    while (tmpOrdi != NULL){

        if (tmpOrdi -> id == id) return tmpOrdi;
        tmpOrdi = tmpOrdi -> suiv;
    }

    return NULL;
}

Booleen rechercherOrdi(Reseau r, int id){

    Ordi * tmp = rechercherOrdiPt(r, id);
    if (tmp != NULL) return VRAI;
    return FAUX;
}

// On ajoute le nouvel ordi en tête dans le réseau =
CodeRetour ajouterOrdi(Reseau * ptr, int id) {
    // Si l'ordi existe déjà, on part 
    if (rechercherOrdiPt(*ptr, id) != NULL){
        printf("[infos] : L'ordinateur %d existe déjà.\n", id);
        afficheMessageCodeRetour(PB_NOEUD_DEJA_EXISTANT);
        return PB_NOEUD_DEJA_EXISTANT;
    }
    // On créé un nouvel ordinateur 
    Ordi * tmpOrdi = (Ordi *) malloc(sizeof(Ordi));
    if (tmpOrdi == NULL){
        printf("[erreur] : Problème d'allocation mémoire dans l'ajout d'ordi.\n");
        afficheMessageCodeRetour(PB_MEMOIRE);
        return PB_MEMOIRE;
    }

    tmpOrdi -> suiv = *ptr;
    tmpOrdi -> id = id;
    tmpOrdi -> listeConnexions = NULL;
    *ptr = tmpOrdi;
    
    return (OK);
}

// a temriner 
// CodeRetour rechercherConnexion(Reseau r, Ordi dep, Ordi arr) {
    
//     if (rechercherOrdi(dep) == FAUX){
//         printf("[infos] : Impossible de chercher la connexion, l'ordinateur de depart %d introuvable.\n", dep -> id);
//         return PB_NOEUD_DEP_NON_EXISTANT;
//     }
    
//     if (rechercherOrdi(arr) == FAUX){
//         printf("[infos] : Impossible de chercher la connexion, l'ordinateur d'arrivée %d n'existe pas.\n", arr -> id);
//         return PB_NOEUD_ARR_NON_EXISTANT;
//     }

    
//     return PB_ARC_DEJA_EXISTANT;
// }


