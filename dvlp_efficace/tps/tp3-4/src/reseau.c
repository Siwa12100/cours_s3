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

CodeRetour  rechercherConnexionPt(Ordi* ptDep, Ordi* ptArr, Connexion ** addrConnexion);

CodeRetour rechercherConnexion(Reseau r, int idDep, int idArr) {
    Ordi * ptDep, *ptArr;
    Connexion* ptConnexion;
    ptDep = rechercherOrdiPt(r, idDep);
    if (ptDep ==NULL){
        printf("[erreur] : L'ordinateur de départ %d est introuvable dans le réseau.\n", idDep);
        return PB_NOEUD_DEP_NON_EXISTANT;
    }
    ptArr = rechercherOrdiPt(r, idArr);
    if (ptArr==NULL){
        printf("[erreur] : L'ordinateur d'arrivée %d est introuvable dans le réseau.\n", idArr);
        return PB_NOEUD_ARR_NON_EXISTANT;
    }

    return rechercherConnexionPt(ptDep, ptArr, &ptConnexion);
}

// On passe un pointeur sur un pointeur de connexion 
CodeRetour rechercherConnexionPt(Ordi* ptDep, Ordi* ptArr, Connexion ** addrConnexion) {
   
   //stopProgramme();
   *addrConnexion = NULL;
   //stopProgramme();

    Connexion * tmpa = ptDep -> listeConnexions;

    while (tmpa != NULL){
        
        if (tmpa -> extremite == ptArr){
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

    // On stocke l'ordinateur de départ de la potentielle connexion
    Ordi * tmpOrdiDep = rechercherOrdiPt(*ptr, idDep);
    // Si on récupère NULL, c'est que l'ordinateur n'existe pas alors on quitte 
    if (tmpOrdiDep == NULL){
        printf("[erreur] : L'ordinateur de départ %d est introuvable, échec de la suppression de la connexion.\n",idDep);
        return PB_NOEUD_DEP_NON_EXISTANT;
    }

    // On récupère l'adresse de l'ordinateur d'arrivée de la potentielle connexion
    Ordi * tmpOrdiArr = rechercherOrdiPt(*ptr, idArr);
    // Là encore, si on récupère NULL, c'est que l'ordi n'existe pas alors on quitte 
    if (tmpOrdiDep == NULL){
        printf("[erreur] : L'ordinateur d'arrivée %d est introuvable, échec de la suppresion de la connexion.\n", idArr); 
        return PB_NOEUD_ARR_NON_EXISTANT;
    }

    // On déclare un pointeur qui va contenir l'adresse de la connexion à supprimer 
    Connexion * tmpConnexionASupprimer;
    
    // On vérifie que la connexion à supprimer existe 
    // le pointeur tmpConnexionASupprimer doit récupérer l'adresse de la connexion à supprimer 
    // donc on le passe en paramètre 
    if (rechercherConnexionPt(tmpOrdiDep, tmpOrdiArr, &tmpConnexionASupprimer) != OUI){
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

    // On récupère la première connexion contenue dans l'ordinateur de départ 
    Connexion * tmpConnexion = tmpOrdiDep -> listeConnexions;

    // Tant que l'on arrive pas au bout de la liste de connexion 
    // On bien tant que la connexion actuelle ne correspond pas à celle à supprimer 
    // alors on passe à la connexion suivante dans la liste 
    while ( tmpConnexion != NULL){

        if (tmpConnexion -> suivant == tmpConnexionASupprimer){
            tmpConnexion -> suivant = tmpConnexionASupprimer -> suivant;
            printf("[temporaire] : tmpConnexionASupprimer -> suivant : %p \n", tmpConnexionASupprimer -> suivant);
            free(tmpConnexionASupprimer);
            return OK;
        }

        tmpConnexion = tmpConnexion -> suivant;        
    }

    // Ne doit jamais pouvoir passer ici en soit...
    return PB_ARC_NON_EXISTANT;
}

CodeRetour destructionOrdi(Reseau * ptr, int id) {
    // On récupère l'adresse de l'ordinateur a supprimer 
    Ordi * OrdiASupprimer =  rechercherOrdiPt(*ptr, id);
    // Si l'adresse est nulle, l'ordinateur n'existe pas, alors on part...
    if (OrdiASupprimer == NULL){
        printf("[erreur] : L'ordinateur %d est introuvable, suppression impossible.\n", id);
        return PB_NOEUD_NON_EXISTANT;
    }
    // On créée un pt temporaire pour parcourir l'ensemble du réseau 
    Ordi * tmpOrdi = *ptr;
    // On parcours l'ensemble du réseau et pour chaque ordinateur : 
    while (tmpOrdi != NULL){
        // S'il existe une connexion entre l'ordinateur courant et celui que l'on souhaite supprimer 
        if (rechercherConnexion(*ptr, tmpOrdi -> id, id) == OUI)
            // Alors on supprime cette connexion
            destructionConnexion(ptr, tmpOrdi -> id, id);
        // On passe à l'ordinateur du réseau suivant 
        tmpOrdi = tmpOrdi -> suiv;
    }
    
    // On déclare un pointeur qui va parcourir la liste des connexions de l'ordi à supprimer 
    Connexion * tmpConnexion = OrdiASupprimer -> listeConnexions;
    // Pointeur qui va stocker temporairement à chaque fois l'adresse de la connexion à libérer 
    Connexion * ConnexionASupprimer;
    // Tant que l'on arrive pas à la fin de la liste de connexions, pour chaque connexion : 
    while (tmpConnexion != NULL){
        // On récupère l'adresse de connexion pour la libérer...
        ConnexionASupprimer = tmpConnexion;
        // On passe à la connexion suivante pour continuer à parcourir la liste de connexions 
        tmpConnexion = tmpConnexion -> suivant;
        // On libère la connexion courante avec un free 
        free(ConnexionASupprimer);
    }

    // On va aller chercher l'ordi juste avant celui à supprimer
    // pour dire à son suivant de pointer sur le suivant de l'ordi à supprimer 

    tmpOrdi = *ptr;

    while (tmpOrdi -> suiv != OrdiASupprimer) tmpOrdi =tmpOrdi -> suiv;
    tmpOrdi -> suiv = OrdiASupprimer -> suiv;

    free(OrdiASupprimer);
    return OK;
}


