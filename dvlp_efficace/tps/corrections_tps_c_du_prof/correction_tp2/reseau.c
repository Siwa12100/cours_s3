#include<stdlib.h>
#include<stdio.h>

#include"reseau.h"




/************************ question 1 ************************/
Reseau initialiser(){
  return NULL;
}

CodeRetour estVide(Reseau r){
  if (r==NULL) return OUI;
  else return NON;
}

/************************ question 2 ************************/
/* affichage du graphe représentant le réseau */
void affiche(Reseau r){
  Noeud *tmp = r;
  Arc *a;
  while (tmp != NULL){
    printf(" %d : \n ",tmp->num);
    a = tmp->listeArc;
    while(a != NULL){
      printf("\t -> %d \n ",a->extremite->num);
      a = a->suivant;
    }
    tmp = tmp->suiv;
  }
}


/************************ question 3 ************************/
/* retourne un pointeur sur le noeud cherché ou NULL sinon */
Noeud * rechercheNoeud(Reseau r, int num){
  Noeud* tmp;

  tmp = r;
  while(tmp != NULL){
    if(tmp->num == num) return tmp;
    tmp = tmp->suiv;
  }
  return tmp;
}

/************************ question 4 ************************/
/*
  retourne OK si l'ajout a été fait
           PB_NOEUD_DEJA_EXISTANT si le noeud existe déjà (ajout non fait)
	   PB_MEMOIRE si problème allocation mémoire
*/
CodeRetour ajoutNoeud(Reseau *pr, int num){
  Noeud * tmp;

  tmp = rechercheNoeud(*pr, num);
  if (tmp != NULL) return PB_NOEUD_DEJA_EXISTANT;
  
  
  tmp=(Noeud*)malloc(sizeof(Noeud));
  if(tmp==NULL) return PB_MEMOIRE;
  tmp->num = num;
  tmp->listeArc = NULL;
  tmp->marque = 0;
  tmp->suiv = *pr;
  *pr = tmp;
  return OK;
}

/************************ question 5 ************************/
/*
  précondition : dep et arr pointent sur deux noeuds réels du réseau
  retourne 
	   NON si l'arc n'existe pas
           OUI s'il existe
 */
CodeRetour existenceArcPt(Noeud* dep, Noeud *arr){
  Arc* tmp;

  tmp = dep->listeArc;
  while(tmp != NULL){
    if(tmp->extremite == arr) return OUI;
    tmp = tmp->suivant;
  }
  return NON;
}


/************************/
/*  retourne
	     PB_NOEUD_DEP_NON_EXISTANT si le noeud de départ n'existe pas
	     PB_NOEUD_ARR_NON_EXISTANT si le noeud d'arrivée n'existe pas
	     NON si l'arc n'existe pas
             OUI s'il existe                                  
*/
CodeRetour existenceConnexion(Reseau r, int dep, int arr){
  Noeud *pa, *pb;

  pa = rechercheNoeud(r, dep);
  if(pa == NULL) return PB_NOEUD_DEP_NON_EXISTANT;
  pb = rechercheNoeud(r, arr);
  if(pb == NULL) return PB_NOEUD_ARR_NON_EXISTANT;

  return existenceArcPt(pa, pb);
}

/************************ question 6 ************************/
/*  retourne OK si l'arc allant de dep à arr a bien été ajouté
             PB_NOEUD_DEP_NON_EXISTANT si dep n'existe pas
	     PB_NOEUD_ARR_NON_EXISTANT si arr n'existe pas
	     PB_ARC_DEJA_EXISTANT si l'arc existe déjà
	     PB_MEMOIRE si problème allocation mémoire
 */
CodeRetour ajoutArc(Reseau r, int dep, int arr){
  Noeud *pa, *pb;
  Arc * tmp;

  pa = rechercheNoeud(r, dep);
  if(pa == NULL) return PB_NOEUD_DEP_NON_EXISTANT;
  pb = rechercheNoeud(r, arr);
  if(pb == NULL) return PB_NOEUD_ARR_NON_EXISTANT;

  if(existenceArcPt(pa,pb) == OUI) return PB_ARC_DEJA_EXISTANT;

  /* sinon on ajoute cet arc */
  tmp=(Arc*)malloc(sizeof(Arc));
  if(tmp == NULL) return PB_MEMOIRE;
  tmp->extremite = pb;
  tmp->suivant = pa->listeArc;
  pa->listeArc = tmp;
  return OK;
}

/************************ question 7 ************************/
/*  précondition dep et arr pointent sur deux noeuds existants du réseau
    retourne OK si la destruction a été effectuée
	     PB_ARC_NON_EXISTANT si l'arc n'existait pas                  
*/
CodeRetour destructionArcPt(Noeud* dep, Noeud* arr){
  Arc * tmp, *tmpav;

  if(existenceArcPt(dep,arr) == NON) return PB_ARC_NON_EXISTANT;
  
  /* sinon on le détruit */
  tmp = dep->listeArc;

  /*si c'est le premier */
  if(tmp->extremite == arr) 
    dep->listeArc = tmp->suivant;
  else{
    while(tmp->extremite != arr){
      tmpav = tmp;
      tmp = tmp->suivant;
    }
    tmpav->suivant = tmp->suivant;
  }
  tmp->extremite = NULL;
  free(tmp);
  return OK;
}
/************************/
/*  retourne OK si destruction effectuée
             PB_NOEUD_DEP_NON_EXISTANT si dep n'existe pas
	     PB_NOEUD_ARR_NON_EXISTANT si arr n'existe pas
	     PB_ARC_NON_EXISTANT si l'arc n'existe pas
*/
CodeRetour destructionArc(Reseau r, int dep, int arr){
  Noeud *pa, *pb;

  pa = rechercheNoeud(r, dep);
  if(pa == NULL) return PB_NOEUD_DEP_NON_EXISTANT;
  pb = rechercheNoeud(r, arr);
  if(pb == NULL) return PB_NOEUD_ARR_NON_EXISTANT;

  return destructionArcPt(pa, pb);
}

/************************ question 8 ************************/
/* lorsque l'on détruit un noeud il faut également détruire 
   tous les arcs qui partent de lui et tous les arcs qui pointent 
   sur lui.
   retourne OK si destruction effectuée
            PB_NOEUD_NON_EXISTANT si num n'existe pas       */
CodeRetour destructionNoeud(Reseau *pr, int num){
  Noeud *ptn, *pt2;
  Arc * tmpa;

  /* on cherche le noeud */
  ptn=rechercheNoeud(*pr, num);

  if(ptn == NULL) return PB_NOEUD_NON_EXISTANT;

  /* on enlève tous les arcs partant de lui */
  while(ptn->listeArc != NULL){
    tmpa = ptn->listeArc;
    ptn->listeArc = tmpa->suivant;
    free(tmpa);
  }

  /* on enlève tous les arcs pointant sur lui */
  pt2 = *pr;
  while(pt2 != NULL){
    destructionArcPt(pt2, ptn);
    pt2 = pt2->suiv;
  }

  /* on détruit le noeud en refaisant d'abord le chainage */
  if(ptn == *pr)
    *pr = (*pr)->suiv;
  else{
    // on place pt2 sur le noeud juste avant ptn
    pt2 = *pr;
    while(pt2->suiv !=ptn)
      pt2 = pt2->suiv;
    pt2->suiv = ptn->suiv;
  }
  free(ptn);
  return OK;
}



/************************ question en plus ************************/
void destructionReseau(Reseau *pr){
  while(*pr != NULL)
    destructionNoeud(pr,(*pr)->num);
}

/************************ question 9 ************************/
int compteNoeud(Reseau r){
  Noeud * pt;
  int cpt;

  pt = r;
  cpt = 0;
  while(pt != NULL){
    pt = pt->suiv;
    cpt++;
  }
  
  return cpt;
}
/************************ question 10 ************************/
int compteArc(Reseau r){
  Noeud * pt;
  Arc *tmp;
  int cpt;

  pt = r;
  cpt = 0;
  while(pt != NULL){
    tmp = pt->listeArc;
    while(tmp != NULL){
      tmp = tmp->suivant;
      cpt++;
    }
    pt = pt->suiv;
  }
  
  return cpt;
}




/*----------------------------------------------------*/

/************************ question 11 - a)  ************************/
/* fonction qui détermine si une machine donnée peut communiquer avec une autre également donnée
   utilise un parcours en profondeur
   retourne PB_NOEUD_DEP_NON_EXISTANT
	    PB_NOEUD_ARR_NON_EXISTANT
	    OUI si dep peut communiquer avec arr
	    NON si dep ne peut pas communiquer avec arr (dep et arr existent)
*/

/*  mise à zéro de la marque de chaque noeud  */
void toutMarquerAZero(Reseau r){
  Noeud * tmp = r;
  while(tmp != NULL){
    tmp->marque = 0;
    tmp = tmp->suiv;
  }
}

CodeRetour visitePourPeutCommuniquer(Noeud * pdep, Noeud * parr){
  Arc* tmpa;

  pdep->marque = 1;
  if(pdep == parr) return OUI;

  tmpa = pdep->listeArc;
  while(tmpa !=NULL){
    if(tmpa->extremite->marque == 0)
      if(visitePourPeutCommuniquer(tmpa->extremite, parr)==OUI)
	return OUI;  
    tmpa = tmpa->suivant;
  }
  return NON;
}

CodeRetour peutCommuniquer(Reseau r, int dep, int arr){
  Noeud *pdep, *parr;

  pdep = rechercheNoeud(r, dep);
  if(pdep == NULL) return PB_NOEUD_DEP_NON_EXISTANT;
  parr = rechercheNoeud(r, arr);
  if(parr == NULL) return PB_NOEUD_ARR_NON_EXISTANT;
  
  toutMarquerAZero(r);

  return visitePourPeutCommuniquer(pdep, parr);
}




/************************ question 11 - b) ************************/
/* fonction qui détermine  et affiche l'ensemble des noeuds avec 
         lesquels un noeud donné peut communiquer
   utilise un parcours en profondeur
   retourne PB_NOEUD_DEP_NON_EXISTANT si le neoud de départ n'existe pas
	    OK si l'affichage a pu se faire
*/

void visiterPourMarquerQuiPeutCommuniquer(Noeud * pdep){
  Arc* tmpa;

  pdep->marque = 1;

  tmpa = pdep->listeArc;
  while(tmpa !=NULL){
    if(tmpa->extremite->marque == 0)
      visiterPourMarquerQuiPeutCommuniquer(tmpa->extremite);
    tmpa = tmpa->suivant;
  }

}

void afficheAvecQuiCommuniquer(Reseau r, int dep){
  Noeud *pdep, *tmp;

  pdep = rechercheNoeud(r, dep);
  if(pdep == NULL){
    printf("problème : %d n'existe pas \n", dep);
    return;
  }
  
  toutMarquerAZero(r);

  visiterPourMarquerQuiPeutCommuniquer(pdep);

  // puis on affiche tous les noeuds qui sont à 1
  printf("les noeuds avec lesquels %d peut communiquer sont : \n", dep);
  tmp = r;
  while(tmp!= NULL){
    if(tmp->marque == 1)
      printf("\t %d \n", tmp->num);
    tmp = tmp->suiv;
  }
}



/***************** Etape 3  :   question 1 ************************/
/* fonction de chargement du réseau en mémoire
   en cas de problème le réseau reste vide
   retourne OK si chargement effectué
            PB_OUVERTURE_FICHIER si pb ouverture fichier
	    PB_RESEAU_ERRONNE si reseau erroné :
	         noeud déjà existant, 
	         connexion entre deux noeuds non existants (un au moins), 
	         ou si connexion déjà existante
	    PB_MEMOIRE si problème allocation mémoire
*/
CodeRetour chargement(char * nomFichier, Reseau * pr){
  FILE * fp;
  int n,m,i,a,b, num;
  char code;

  *pr = NULL;
  fp = fopen(nomFichier,"rt");
  if(fp == NULL)
    return PB_OUVERTURE_FICHIER;
  
  /* lecture du nombre de noeuds */
  fscanf(fp,"%d",&n);

  /* lecture du nombre de connexions */
  fscanf(fp,"%d",&m);

  /* lecture des noeuds */
  for(i=0;i<n;i++){
    fscanf(fp,"%d",&num);
    code = ajoutNoeud(pr,num);
    if(code == PB_NOEUD_DEJA_EXISTANT ) return PB_RESEAU_ERRONNE;
    else if (code == PB_MEMOIRE) return PB_MEMOIRE;
 }

  /* lecture des connexions */
  for(i=0;i<m;i++){
    fscanf(fp,"%d",&a);
    fscanf(fp,"%d",&b);

    code = ajoutArc(*pr,a,b);
    if(code != OK){
      destructionReseau(pr);
      fclose(fp);
      if(code == PB_MEMOIRE) return PB_MEMOIRE;
      else return PB_RESEAU_ERRONNE;
    }
  }    

  fclose(fp);
  return OK;
}

/*----------------------------------------------------*/
/* fonction de sauvegarde du réseau en mémoire */
/*   retourne OK si sauvegarde ok
              PB_OUVERTURE_FICHIER si pb ouverture fichier
*/
CodeRetour sauvegarde(char * nomFichier, Reseau r){
  int nb;
  FILE *fp;
  Noeud *ptn;
  Arc *pta;
  
  fp = fopen(nomFichier,"wt");
  if(fp == NULL) return PB_OUVERTURE_FICHIER;
  
  nb = compteNoeud(r);
  fprintf(fp,"%d\n", nb);

  nb = compteArc(r);
  fprintf(fp,"%d\n", nb);

  ptn = r;
  while(ptn != NULL){
    fprintf(fp, "%d ",ptn->num);
    ptn = ptn->suiv;
  }
  fprintf(fp, "\n");
  
  ptn = r;
  while(ptn != NULL){
    pta = ptn->listeArc;
    while(pta != NULL){
      fprintf(fp, "%d %d\n", ptn->num, pta->extremite->num); 
      pta= pta->suivant;
    }
    ptn = ptn->suiv;
  }

  fclose(fp);
  return OK;
}

/******************* Etape 3 :  question 2 ************************/
/* fonction qui exporte le réseau dans un fichier dot pour pouvoir 
   être lu par dotty 
   retourne OK si sauvegarde effectuée
            PB_OUVERTURE_FICHIER si pb ouverture fichier
*/
CodeRetour exporte(char * nomFichier, Reseau r){
  FILE *fp;
  Noeud *tmp;
  Arc *tmpa;
  char c = '"';

  fp = fopen(nomFichier,"wt");
  if(fp == NULL) return PB_OUVERTURE_FICHIER;

  fprintf(fp,"digraph family\n");
  fprintf(fp,"{\n");

  /* sauvegarde des sommets */
  tmp = r;
  while(tmp != NULL){
    fprintf(fp,"%d [label= %cNoeud %d%c]\n",tmp->num,c,tmp->num,c);
    tmp = tmp->suiv;
  }
    
  /* sauvegarde des connexions */
  tmp = r;
  while(tmp != NULL){
    tmpa = tmp->listeArc;
    while(tmpa != NULL){
      fprintf(fp,"%d->%d \n",tmp->num, tmpa->extremite->num);
      tmpa = tmpa->suivant;
    }
    tmp = tmp->suiv;
  }
  fprintf(fp,"}\n");

  fclose(fp);
  return OK;
}

