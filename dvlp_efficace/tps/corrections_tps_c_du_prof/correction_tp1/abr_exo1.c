#include "abr_exo1.h"
#include <stdio.h>
#include <stdlib.h>

ABR creerArbreVide(){
  return NULL;
}

Booleen estArbreVide(ABR a){
  return (a==NULL)? VRAI:FAUX ;
}

NoeudABR* creerNoeud(int val){
  NoeudABR* tmp = (NoeudABR*) malloc(sizeof(NoeudABR));
  if(tmp == NULL) exit(1);
  tmp->fg = NULL;
  tmp->fd = NULL;
  tmp->val = val;
  return tmp;
}

void insererEnFeuille(ABR* pta, int val){
  if(*pta == NULL){
    *pta = creerNoeud(val);
  }
  else if (val <= (*pta)->val){
    insererEnFeuille(&(*pta)->fg, val);
  }
  else{
    insererEnFeuille(&(*pta)->fd, val);
  }
}

void viderArbre(ABR* pta){
  if(*pta != NULL){
    viderArbre(&(*pta)->fg);
    viderArbre(&(*pta)->fd);
    free(*pta);
    *pta = NULL;
  }
}

void afficherCroissant(ABR a){
  if (a!= NULL){
    afficherCroissant(a->fg);
    printf("%d, ", a->val);
    afficherCroissant(a->fd);
  }
}

void afficherDecroissant(ABR a){
  if(a!=NULL){
    afficherDecroissant(a->fd);
    printf("%d, ", a->val);
    afficherDecroissant(a->fg);
  }
}

// pour l'affichage couché : 

void afficherNtab(int n){for(int i = 0; i<n; i++) printf("\t"); }

void afficherCoucheRec(ABR a, int retrait){
  if(a->fd !=NULL){
    afficherCoucheRec(a->fd, retrait+1);
    afficherNtab(retrait); printf("    / \n");
  }

  afficherNtab(retrait); printf("%d\n", a->val);
  
  if(a->fg !=NULL){
    afficherNtab(retrait); printf("    \\ \n");
    afficherCoucheRec(a->fg,retrait+1);
  }
}


void afficherCouche(ABR a){
  if(a!=NULL)
    afficherCoucheRec(a,0);
}



Booleen rechercherVal(ABR a, int val){
  if(a==NULL) return FAUX;
  if(a->val == val) return VRAI;
  if(val < a->val) return rechercherVal(a->fg,val);
  else return rechercherVal(a->fd,val);
}

//--------------------------------------------------------

// pour la suppression

// supprime le noeud contenant la valeur max de l'arbre 
// et retourne sa valeur.
//  ATTENTION : *pta doit être un arbre non vide
int oterMax(ABR * pta){
  NoeudABR * tmp;
  int val;
  if((*pta)->fd==NULL){
    tmp = *pta;
    val = tmp->val;
    *pta = (*pta)->fg;
    free(tmp);
  }
  else{
    val = oterMax(&(*pta)->fd);
  }
  return val;
}

Booleen supprimerVal(ABR *pta, int val){
  NoeudABR* tmp;
  Booleen b;

  if(*pta==NULL) return FAUX;

  // si la valeur est à la racine de l'arbre
  if ((*pta)->val == val){
    if((*pta)->fg == NULL){
      tmp = *pta;
      *pta = (*pta)->fd;
      free(tmp);          ////////////////  et non pas free(*A);
    }
    else if((*pta)->fd == NULL ){
      tmp = *pta;
      *pta = (*pta)->fg;
      free(tmp);          ////////////////  et non pas free(*A);
    }
    else  /// cad si ((*pta)->fd != NULL && (*pta)->fg != NULL)
      (*pta)->val = oterMax(&(*pta)->fg);

    return VRAI;   
  }

  // sinon on continue dans la suite de l'arbre ( à gauche ou à droite)
  else if (val < (*pta)->val){
    b = supprimerVal(&(*pta)->fg, val);
  }
  else{
    b =  supprimerVal(&(*pta)->fd, val);
  }
  
  return b;
}
