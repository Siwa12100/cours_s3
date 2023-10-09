#include "avl_exo2.h" // les AVL
#include <stdio.h>
#include <time.h>

void testExo2(){
  Booleen b;
  AVL a = creerArbreVide();

  if(estArbreVide(a)) printf("OK : l'arbre est vide à sa création\n");
  else printf("ERREUR : l'arbre devrait être vide à sa création\n");
  
  insererEquilibre(&a, 10);
  if(! estArbreVide(a))
    printf("OK : l'arbre n'est pas vide après une insertion\n");
  else
    printf("ERREUR : l'arbre devrait ne pas être vide après une insertion\n");

  afficherCouche(a);
  insererEquilibre(&a, 5);
  afficherCouche(a);
  insererEquilibre(&a, 15);
  afficherCouche(a);
  insererEquilibre(&a, 12);
  afficherCouche(a);
  insererEquilibre(&a, 7);
  afficherCouche(a);
  insererEquilibre(&a, 8);
  afficherCouche(a);
  insererEquilibre(&a, 9);

  printf("après insertion de 10,5,15,12,7,8 et 9\n");
  
  afficherCouche(a);

  printf(" suppression de 5\n");
  b=supprimerVal(&a,5);

  if(b) printf("OK : 5 a été supprimé\n");
  else printf("ERREUR : 5 n'a pas pu être supprimé\n");
  
  afficherCouche(a);
  
  viderArbre(&a);
  
  if(estArbreVide(a)) printf("OK : l'arbre a bien été vidé\n");
  else printf("ERREUR : l'arbre n'a pas été vidé visiblement\n");

}

void mesureTemps(int nb){
  Booleen b;
  AVL a = creerArbreVide();
  clock_t t;
  double temps;
  
  printf("TEST pour AVL de %d noeuds : \n", nb);
  
  t = clock();
  for(int i = 1; i<=nb ; i++)
    insererEquilibre(&a, i);
  t = clock() - t;
  temps = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("temps de la construction : %f s\n", temps);

  t = clock();
  b=rechercherVal(a, -1);
  t = clock() - t;
  temps = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("temps pour la recherche de -1 : %f s\n", temps);

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
  //testExo2();
  testExo3();
  
  return 0;
}
