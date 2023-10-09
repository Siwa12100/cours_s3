#include<stdlib.h>
#include<stdio.h>

#include "reseau.h"
#include "codeRetour.h"

int menu(){
  int choix;
  printf("--------------------------------\n");
  printf("que desirez vous ?\n");
  printf("   0- quitter\n");
  printf("   1- ajouter un noeud \n");
  printf("   2- ajouter une connexion\n");
  printf("   3- rechercher un noeud\n");
  printf("   4- rechercher une connexion \n");
  printf("   5- detruire un noeud\n");
  printf("   6- detruire une connexion \n");
  printf("   7- detruire tout le reseau \n");
  printf("   8- connaitre le nombre de noeuds \n");
  printf("   9- connaitre le nombre de connexions \n");
  printf("   10- charger un reseau  \n");
  printf("   11- sauvegarder un reseau  \n");
  printf("   12- exporter un reseau  \n");
  printf("   13- afficher le reseau (affichage de base) \n");
  printf("   14- savoir si une machine peut communiquer avec une autre\n");
  printf("   15- connaitre toutes les machines avec lesquelles peut communiquer une machine donnée\n");
  printf("--------------------------------\n");
  scanf("%d", &choix);
  return choix;
}


int main(void){
  Reseau r;
  int choix, num, num2;
  CodeRetour code;
  Noeud * ptn;

  char nomFichier[30];

  choix = 12;
  r = initialiser();

  while(choix != 0){
    choix = menu();
    
    switch(choix){
    case 0 : printf("au revoir \n");
      break;
    case 1: 
      printf("donner le numero du noeud a ajouter : ");
      scanf("%d", &num);
      code = ajoutNoeud(&r, num);
      printf("ajout du noeud %d dans le réseau : \n\t", num);
      afficheMessageCodeRetour(code); printf("\n");
      break;

    case 2: 
      printf("donner les deux extremites de la connexion a ajouter \n");
      printf("(2 numeros separes par un espace) : ");
      scanf("%d %d", &num, &num2);
      code = ajoutArc(r, num, num2);
      printf("ajout de l'arc %d -> %d : \n\t", num, num2);
      afficheMessageCodeRetour(code); printf("\n");
      break;

    case 3:       
      printf("donner le numero du noeud à rechercher : ");
      scanf("%d", &num);
      ptn=rechercheNoeud(r,num);
      if(ptn != NULL) printf("noeud trouve \n");
      else printf("noeud non trouve \n");
      break;

    case 4: 
      printf("donner les deux extremites de la connexion à rechercher \n");
      printf("(2 numeros séparés par un espace) : ");
      scanf("%d %d", &num, &num2);
      code = existenceConnexion(r, num, num2);
      printf("l'arc %d ->%d existe-t-il? ", num, num2);
      afficheMessageCodeRetour(code); printf("\n");
      break;

    case 5:
      printf("donner le numero du noeud à détruire : ");
      scanf("%d", &num);
      code = destructionNoeud(&r,num);
      printf("destruction du noeud %d : ",num);
      afficheMessageCodeRetour(code); printf("\n");
      break;

    case 6: 
      printf("donner les deux extremites de la connexion a detruire \n");
      printf("(2 numeros separes par un espace) : ");
      scanf("%d %d", &num, &num2);
      code = destructionArc(r, num, num2);
      printf("destruction de la connexion %d->%d : ",num, num2);
      afficheMessageCodeRetour(code); printf("\n");
      break;

    case 7:
      destructionReseau(&r);
      break;

    case 8:
      num = compteNoeud(r);
      printf("le reseau comporte %d noeuds \n",num);
      break;

    case 9: 
      num = compteArc(r);
      printf("le reseau comporte %d arcs \n",num);
      break;

    case 10: //charger
      printf("quel est le nom du fichier contenant le reseau? ");
      scanf("%s",nomFichier);
      destructionReseau(&r);   /// destruction du réseau déjà existant
      code = chargement(nomFichier, &r);
      printf("chargement du réseau à partir de %s : ",nomFichier);
      afficheMessageCodeRetour(code); printf("\n");
      break;

    case 11: //sauvegarder
      printf("dans quel fichier voulez vous sauver le reseau? ");
      scanf("%s",nomFichier);
      code= sauvegarde(nomFichier,r);
      printf("sauvegarde dans %s : ", nomFichier);
      afficheMessageCodeRetour(code); printf("\n");
      break;

    case 12: //exporter
      printf("dans quel fichier voulez vous exporter le reseau? ");
      scanf("%s",nomFichier);
      code= exporte(nomFichier,r);
      printf("export dans %s : ", nomFichier);
      afficheMessageCodeRetour(code); printf("\n");
      break;

    case 13 :
      affiche(r);
      break;
      
    case 14:
      printf("numéro de la première machine : ");
      scanf("%d", &num);
      printf("numéro de la deuxième machine : ");
      scanf("%d", &num2);
      
      code = peutCommuniquer(r,num,num2);
      printf("est-ce que %d peut communiquer avec %d : ", num,num2);
      afficheMessageCodeRetour(code); printf("\n");
      break;

    case 15:
      printf("numéro de la machine : ");
      scanf("%d", &num);
      afficheAvecQuiCommuniquer(r,num);
      break;

    default : printf("erreur de frappe ! \n"); 
      break;
      
    }
  }
  return 0;
}
