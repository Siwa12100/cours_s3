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

CodeRetour  rechercherConnexionPt(Reseau r, int idDep, int idArr, Connexion ** addrConnexion);

CodeRetour rechercherConnexion(Reseau r, int idDep, int idArr) {

    if (rechercherOrdi(r, idDep) == FAUX){
        printf("[erreur] : L'ordinateur de départ %d est introuvable dans le réseau.\n", idDep);
        return PB_NOEUD_DEP_NON_EXISTANT;
    }

    if (rechercherOrdi(r, idArr) == FAUX){
        printf("[erreur] : L'ordinateur d'arrivée %d est introuvable dans le réseau.\n", idArr);
        return PB_NOEUD_ARR_NON_EXISTANT;
    }

    return rechercherConnexionPt(r, idDep, idArr, NULL);
}

// On passe un pointeur sur un pointeur de connexion 
CodeRetour rechercherConnexionPt(Reseau r, int idDep, int idArr, Connexion ** addrConnexion) {
   
   //stopProgramme();
   *addrConnexion = NULL;
   stopProgramme();

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
        
        if (tmpa -> extremite == tmpOrdiExtrem){
            *addrConnexion = tmpa;
             return OUI;
        }
        tmpa = tmpa -> suivant;
    }

    *addrConnexion = NULL;
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

CodeRetour destructionConnexion(Reseau * ptr, int idDep, int idArr) {

    stopProgramme();

    // On stocke l'ordinateur de départ de la potentielle connexion
    Ordi * tmpOrdiDep = rechercherOrdiPt(*ptr, idDep);
    // Si on récupère NULL, c'est que l'ordinateur n'existe pas alors on quitte 
    if (tmpOrdiDep == NULL){
        printf("[erreur] : L'ordinateur de départ %d est introuvable, échec de la suppression de la connexion.\n",idDep);
        return PB_NOEUD_DEP_NON_EXISTANT;
    }

    //stopProgramme();

    // On récupère l'adresse de l'ordinateur d'arrivée de la potentielle connexion
    Ordi * tmpOrdiArr = rechercherOrdiPt(*ptr, idArr);
    // Là encore, si on récupère NULL, c'est que l'ordi n'existe pas alors on quitte 
    if (tmpOrdiDep == NULL){
        printf("[erreur] : L'ordinateur d'arrivée %d est introuvable, échec de la suppresion de la connexion.\n", idArr); 
        return PB_NOEUD_ARR_NON_EXISTANT;
    }
    // On déclare un pointeur qui va contenir l'adresse de la connexion à supprimer 
    Connexion * tmpConnexionASupprimer = 6;
    

    // =======================
    // verif temporaire ... :
    printf("\n - tmpConnexionASupprimer (1) : %p \n\n\n", tmpConnexionASupprimer);

    //stopProgramme();

    // On vérifie que la connexion à supprimer existe 
    // le pointeur tmpConnexionASupprimer doit récupérer l'adresse de la connexion à supprimer 
    // donc on le passe en paramètre 
    if (rechercherConnexionPt(*ptr, idDep, idArr, &tmpConnexionASupprimer) != OUI){
        // Si on ne récupère pas oui, c'est que la connexion d'existe pas alors on quitte 
        printf("[erreur] : connexion entre %d et %d inexistante, suppression impossible.\n", idDep, idArr);
        return PB_ARC_NON_EXISTANT;
    }

    // Si la connexion à supprimer est nulle, alors on quitte 
    // C'est simplement une mesure supplémentaire de sécurité...
    if (tmpConnexionASupprimer == NULL){
        printf("[erreur] : Connexion introuvable, erreur dans la fonction de recherche pointée.\n");
        return PB_ARC_NON_EXISTANT;
    }


    // =========================
    // verifications temporaires : 
    // printf("\n\n tmpOrdiDep : %p \n\n", tmpOrdiDep);
    // printf(" \n\n tmpOrdiDep -> listeConnexions : %p \n\n", tmpOrdiDep -> listeConnexions);


    // On récupère la première connexion contenue dans l'ordinateur de départ 
    Connexion * tmpConnexion = tmpOrdiDep -> listeConnexions;
    


    // =========================
    // verifications temporaires :
    printf("\n\n - tmpConnexion : %p\n", tmpConnexion);
    printf("\n - tmpConnexionASupprimer : %p \n\n\n", tmpConnexionASupprimer);


    // Tant que l'on arrive pas au bout de la liste de connexion 
    // On bien tant que la connexion actuelle ne correspond pas à celle à supprimer 
    // alors on passe à la connexion suivante dans la liste 
    while (tmpConnexion != tmpConnexionASupprimer || tmpConnexion != NULL) tmpConnexion = tmpConnexion -> suivant;

    // Si la dernière connexion est nulle, alors ce que l'on a pas trouvé la connexion à supprimer 
    // donc on part.... (mais enfin normalement ce n'est pas censé arrivé....)
    if (tmpConnexion == NULL){
        printf("[erreur] : Impossible de trouver l'adresse de la connexion à supprimer, échec de la suppression.\n");
        return PB_ARC_NON_EXISTANT;
    }

    // Sinon, le pointeur sur la connexion actuelle de l'ordinateur passe directement à la connexion suivante
    tmpConnexion = tmpConnexion -> suivant;
    // Et on supprimer la connexion à supprimer 
    free(tmpConnexionASupprimer);

    // On retourne que la connexion a bien été supprimée 
    return OK;
}


