#include "abr_exo1.h"  // les ABR
#include <stdio.h>
#include <time.h>


void testExo1(){
  Booleen b;
  ABR a = creerArbreVide();

  if(estArbreVide(a)) printf("OK : l'arbre est vide à sa création\n");
  else printf("ERREUR : l'arbre devrait être vide à sa création\n");
  
  insererEnFeuille(&a, 10);
  if(! estArbreVide(a))
    printf("OK : l'arbre n'est pas vide après une insertion\n");
  else
    printf("ERREUR : l'arbre devrait ne pas être vide après une insertion\n");

  insererEnFeuille(&a, 5);
  insererEnFeuille(&a, 15);
  insererEnFeuille(&a, 7);
  insererEnFeuille(&a, 20);

  printf("après insertion de 10,5,15,7 et 20\n");
  
  afficherCouche(a);

  insererEnFeuille(&a, 6);
  insererEnFeuille(&a, 3);
  insererEnFeuille(&a, 8);
  insererEnFeuille(&a, 2);
  insererEnFeuille(&a, 4);
  insererEnFeuille(&a, 17);

  printf("après insertion de 6,3,8,2,4 et 17\n");
  afficherCouche(a);
  
  afficherCroissant(a); printf("\n");
  afficherDecroissant(a);printf("\n");

  b = rechercherVal(a, 7);
  if(b) printf("OK : 7 trouvé\n");
  else printf("ERREUR : 7 pas trouvé\n");

  b = rechercherVal(a, 16);
  if(b) printf("ERREUR : 16 trouvé\n");
  else printf("OK : 16 pas trouvé\n");
  
  printf(" suppression de 10\n");
  b=supprimerVal(&a,10);

  if(b) printf("OK : 10 a été supprimé\n");
  else printf("ERREUR : 10 n'a pas pu être supprimé\n");
  
  afficherCouche(a);

  viderArbre(&a);
  
  if(estArbreVide(a)) printf("OK : l'arbre a bien été vidé\n");
  else printf("ERREUR : l'arbre n'a pas été vidé visiblement\n");

}

void mesureTemps(int nb){
  Booleen b;
  ABR a = creerArbreVide();
  clock_t t;
  double temps;

  printf("TEST pour ABR déséquilibré de %d noeuds : \n", nb);
  
  t = clock();
  for(int i = 1; i<=nb ; i++)
    insererEnFeuille(&a, i);
  t = clock() - t;
  temps = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("\t temps de la construction : %f s\n", temps);

  t = clock();
  b = rechercherVal(a, -1);
  t = clock() - t;
  temps = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("\t temps pour la recherche de -1 : %f s\n", temps);

  t = clock();
  b = rechercherVal(a, nb/2);
  t = clock() - t;
  temps = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("\t temps pour la recherche de %d : %f s\n", nb/2, temps);

  t = clock();
  b = rechercherVal(a, nb+1);
  t = clock() - t;
  temps = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("\t temps pour la recherche de %d : %f s\n", nb+1, temps);

  t = clock();
  viderArbre(&a);
  t = clock() - t;
  temps = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("\t temps pour vider l'arbre : %f s\n\n", temps);
}


void testExo3(){
  mesureTemps(10000);
  mesureTemps(50000);
  mesureTemps(100000);
  
}

int main(void){
  // testExo1();
  testExo3();
  
  return 0;
}
