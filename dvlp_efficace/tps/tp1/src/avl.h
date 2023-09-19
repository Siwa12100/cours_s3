#ifndef def_avl_h
#define dev_avl_h 
#include "abr.h"
// typedef struct noeud {
//     int h; /**<Hauteur du noeud*/
//     int val; /**< Valeur stockée dans le nœud. */
//     struct noeud *fg; /**< Pointeur vers le sous-arbre gauche. */
//     struct noeud *fd; /**< Pointeur vers le sous-arbre droit. */
// } Noeud;

//typedef Noeud * ArbreBin;
typedef Abr Avl;

void mettreAjourHauteur(Avl * v);

#endif
