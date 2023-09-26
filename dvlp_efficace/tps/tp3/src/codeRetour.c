#include "codeRetour.h"
#include <stdio.h>

void afficheMessageCodeRetour(CodeRetour code){
  switch(code){
  case NON :
    printf("non \n");
    break;
  case OUI:
    printf("oui \n");
    break;
  case OK :
    printf("ok, opération effectuée \n");
    break;
  case PB_MEMOIRE:
    printf("problème mémoire \n");
    break;
  case PB_NOEUD_DEJA_EXISTANT:
    printf("problème : noeud déjà existant \n");
    break;
  case PB_NOEUD_DEP_NON_EXISTANT:
    printf("problème : noeud de départ non existant \n");
    break;
  case PB_NOEUD_ARR_NON_EXISTANT:
    printf("problème : noeud d'arrivée non existant \n");
    break;
  case PB_NOEUD_NON_EXISTANT:
    printf("problème : noeud non existant \n");
    break;
  case PB_ARC_DEJA_EXISTANT:
    printf("problème : arc déjà existant \n");
    break;
  case PB_ARC_NON_EXISTANT:
    printf("problème : arc non existant \n");
    break;
  case PB_OUVERTURE_FICHIER:
    printf("problème ouverture du fichier \n");
    break;
  case PB_RESEAU_ERRONNE:
    printf("problème : réseau erroné _\n");
    break;
  default :
    printf("ERREUR : code retour inconnu\n");
  }


}