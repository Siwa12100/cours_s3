#include "avl_exo2.h"
#include <stdio.h>
#include <stdlib.h>

AVL creerArbreVide(){
  return NULL;
}

Booleen estArbreVide(AVL a){
  return (a==NULL)? VRAI:FAUX ;
}

void viderArbre(AVL* pta){
  if(*pta != NULL){
    viderArbre(&(*pta)->fg);
    viderArbre(&(*pta)->fd);
    free(*pta);
    *pta = NULL;
  }
}

void afficherCroissant(AVL a){
  if (a!= NULL){
    afficherCroissant(a->fg);
    printf("%d, ", a->val);
    afficherCroissant(a->fd);
  }
}

void afficherDecroissant(AVL a){
  if(a!=NULL){
    afficherDecroissant(a->fd);
    printf("%d, ", a->val);
    afficherDecroissant(a->fg);
  }
}

// pour l'affichage couché : 

void afficherNtab(int n){for(int i = 0; i<n; i++) printf("\t"); }

void afficherCoucheRec(AVL a, int retrait){
  if(a->fd !=NULL){
    afficherCoucheRec(a->fd, retrait+1);
    afficherNtab(retrait); printf("    / \n");
  }

  afficherNtab(retrait); printf("%d (%d)\n", a->val, a->h);
  
  if(a->fg !=NULL){
    afficherNtab(retrait); printf("    \\ \n");
    afficherCoucheRec(a->fg,retrait+1);
  }
}

void afficherCouche(AVL a){
  if(a!=NULL)
    afficherCoucheRec(a,0);
}

Booleen rechercherVal(AVL a, int val){
  if(a==NULL) return FAUX;
  if(a->val == val) return VRAI;
  if(val < a->val) return rechercherVal(a->fg,val);
  else return rechercherVal(a->fd,val);
}

// précondition : a n'est pas vide
void mettreAjourHauteur(AVL a){
  int hg, hd;
  if(a->fg==NULL) hg = -1;
  else hg = a->fg->h;
  
  if(a->fd==NULL) hd = -1;
  else hd = a->fd->h;

  if(hg>hd) a->h = 1+hg;
  else a->h = 1+hd;
}

// ------------ pour les rotations

void rotationGauche(AVL* pta){
  NoeudAVL* racine = (*pta)->fd;
  (*pta)->fd = racine->fg;
  mettreAjourHauteur(*pta);
  racine->fg = *pta;
  mettreAjourHauteur(racine);
  *pta = racine;  
}

void rotationDroite(AVL* pta){
  NoeudAVL* racine = (*pta)->fg;
  (*pta)->fg = racine->fd;
  mettreAjourHauteur(*pta);
  racine->fd = *pta;
  mettreAjourHauteur(racine);
  *pta = racine;
}

NoeudAVL* creerNoeud(int val){
  NoeudAVL* tmp = (NoeudAVL*) malloc(sizeof(NoeudAVL));
  if(tmp == NULL) exit(1);
  tmp->fg = NULL;
  tmp->fd = NULL;
  tmp->val = val;
  tmp->h = 0;
  return tmp;
}

void reequilibrer(AVL* pta){
  int hg, hd, hgf, hdf;
  hg = ((*pta)->fg != NULL)? (*pta)->fg->h : -1;
  hd = ((*pta)->fd != NULL)? (*pta)->fd->h : -1;

  if(hg - hd == 2){ // déséquilibre : hg > hd de 2
    hgf = ((*pta)->fg->fg != NULL)? (*pta)->fg->fg->h : -1;
    hdf = ((*pta)->fg->fd != NULL)? (*pta)->fg->fd->h : -1;
    if(hdf > hgf) rotationGauche(&(*pta)->fg);
    rotationDroite(pta);
  }

  else if(hd - hg == 2){ // déséquilibre : hd > hg de 2
    hgf = ((*pta)->fd->fg != NULL)? (*pta)->fd->fg->h : -1;    /////
    hdf = ((*pta)->fd->fd != NULL)? (*pta)->fd->fd->h : -1;    /////
    if(hgf > hdf) rotationDroite(&(*pta)->fd);
    rotationGauche(pta);
  }
  
  else{ // pas de déséquilibre, on remet juste la hauteur à jour
    if(hd > hg) (*pta)->h = hd+1;
    else (*pta)->h = hg+1;
  }
}

// version insertion qui conserve l'équilibre de l'AVL
void insererEquilibre(AVL* pta, int val){
  if(*pta == NULL){
    *pta = creerNoeud(val);
  }
  else{
    if (val <= (*pta)->val){
      insererEquilibre(&(*pta)->fg, val);
    }
    else{
      insererEquilibre(&(*pta)->fd, val);
    }
    reequilibrer(pta);
  }
}
  
  
// pour la suppression
// supprime le noeud contenant la valeur max de l'arbre 
// et retourne sa valeur.
//  ATTENTION : *pta doit être un arbre non vide
int oterMax(AVL * pta){
  NoeudAVL * tmp;
  int val;
  if((*pta)->fd==NULL){
    tmp = *pta;
    val = tmp->val;
    *pta = (*pta)->fg;
    free(tmp);
  }
  else{
    val = oterMax(&(*pta)->fd);
    reequilibrer(pta);
  }
  return val;
}

Booleen supprimerVal(AVL *pta, int val){
  NoeudAVL* tmp;
  Booleen b;

  if(*pta==NULL) return FAUX;

  // si la valeur est à la racine de l'arbre
  if ((*pta)->val == val){
    if((*pta)->fg == NULL){
      tmp = *pta;
      *pta = (*pta)->fd;
      free(tmp);
      // rien à faire pour la hauteur
      // et pas de ré-èquilibration à faire ici
    }
    else if((*pta)->fd == NULL ){
      tmp = *pta;
      *pta = (*pta)->fg;
      free(tmp);       
      // rien à faire pour la hauteur
      // et pas de ré-èquilibration à faire
    }
    else{  /// cad si ((*pta)->fd != NULL && (*pta)->fg != NULL)
      (*pta)->val = oterMax(&(*pta)->fg);
      reequilibrer(pta);
    }
    return VRAI;   
  }

  // sinon on continue dans la suite de l'arbre ( à gauche ou à droite)
  else{
    if (val < (*pta)->val){
      b = supprimerVal(&(*pta)->fg, val);
    }
    else{
      b =  supprimerVal(&(*pta)->fd, val);
    }
    if(b) reequilibrer(pta);
  }
  
  return b;
}

