#include "reseau.h"
#include "codeRetour.h"
#include <stdio.h>
#include <stdlib.h>

void stopProgramme(void) {
    char c;
    printf("\n\n\n [temporaire] : Passage ici --> Appuyez sur touche pour continuer : ");
    scanf("%c", &c);
    printf("%c \n\n\n", c);
}

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
            tempCo = tempCo -> suivant;
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
        //afficheMessageCodeRetour(PB_NOEUD_DEJA_EXISTANT);
        return PB_NOEUD_DEJA_EXISTANT;
    }
    // On créé un nouvel ordinateur 
    Ordi * tmpOrdi = (Ordi *) malloc(sizeof(Ordi));
    if (tmpOrdi == NULL){
        printf("[erreur] : Problème d'allocation mémoire dans l'ajout d'ordi.\n");
        //afficheMessageCodeRetour(PB_MEMOIRE);
        return PB_MEMOIRE;
    }

    tmpOrdi -> suiv = *ptr;
    tmpOrdi -> id = id;
    tmpOrdi -> listeConnexions = NULL;
    *ptr = tmpOrdi;
    
    return (OK);
}

CodeRetour rechercherConnexionPt(Reseau r, int idDep, int idArr);

CodeRetour rechercherConnexion(Reseau r, int idDep, int idArr) {

    if (rechercherOrdi(r, idDep) == FAUX){
        printf("[erreur] : L'ordinateur de départ %d est introuvable dans le réseau.\n", idDep);
        return PB_NOEUD_DEP_NON_EXISTANT;
    }

    if (rechercherOrdi(r, idArr) == FAUX){
        printf("[erreur] : L'ordinateur d'arrivée %d est introuvable dans le réseau.\n", idArr);
        return PB_NOEUD_ARR_NON_EXISTANT;
    }

    return rechercherConnexionPt(r, idDep, idArr);
}

CodeRetour rechercherConnexionPt(Reseau r, int idDep, int idArr) {

    Ordi * tmpOrdiDep = rechercherOrdiPt(r, idDep);
    if (tmpOrdiDep == NULL){
        printf("[erreur] : L'ordinateur %d est introuvable. Particulièrement problématique dans cette fonction...\n", idDep);
        return PB_NOEUD_DEP_NON_EXISTANT;
    }

    Ordi * tmpOrdiExtrem = rechercherOrdiPt(r, idArr);
    if (tmpOrdiExtrem == NULL){
        printf("[erreur] : L'ordinateur %d est introuvable. Particulièrement problématique dans cette fonction...\n", idArr);
        return PB_NOEUD_DEP_NON_EXISTANT;
    }

    Connexion * tmpa = tmpOrdiDep -> listeConnexions;

    while (tmpa != NULL){
        
        if (tmpa -> extremite == tmpOrdiExtrem) return OUI;
        tmpa = tmpa -> suivant;
    }

    return NON;
}

CodeRetour ajouterConnexion(Reseau * ptr, int idDep, int idArr) {

    Ordi * tmpOrdiDep = rechercherOrdiPt(*ptr, idDep);
    if (tmpOrdiDep == NULL) {
        printf("[erreur] : L'ordinateur de départ %d est introuvable, impossible de créer une connexion.\n", idDep);
        return PB_NOEUD_DEP_NON_EXISTANT;
    }

    Ordi * tmpOrdiArr = rechercherOrdiPt(*ptr, idArr);
    if (tmpOrdiArr == NULL){
        printf("[erreur] : L'ordinateur d'arrivée %d est introuvable, impossible de créer une connexion.\n", idArr);
        return PB_NOEUD_ARR_NON_EXISTANT;
    }

    if (rechercherConnexion(*ptr, idDep, idArr) == OUI){
        printf("[erreur] : La connexion entre les ordinateurs %d et %d existe déjà.\n", idDep, idArr);
        return PB_ARC_DEJA_EXISTANT;
    }

    Connexion * tmpConnexion = (Connexion *) malloc (sizeof(Connexion));
    if (tmpConnexion == NULL){
        printf("[erreur] : soucis d'allocation mémoire dans la création d'une connexion.\n");
        return PB_MEMOIRE;
    }

    tmpConnexion -> extremite = tmpOrdiArr;
    tmpConnexion -> suivant = tmpOrdiDep -> listeConnexions;
    tmpOrdiDep -> listeConnexions = tmpConnexion;

    return OK;
}


