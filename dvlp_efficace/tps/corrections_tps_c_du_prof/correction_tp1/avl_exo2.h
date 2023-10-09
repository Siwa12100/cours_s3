/** 
    \file avl_exo2.h
    \author C. SIMON
    \date 02/07/2022
    \brief package des AVL : structure et fonctionnalités de base 
 */

#ifndef AVL_EXO2_H
#define AVL_EXO2_H

#include "pratique.h"




/**
   \brief structure de noeud pour un AVL 
 */
typedef struct noeudAVL{
  int val; /**< valeur contenue dans le noeud */
  struct noeudAVL* fg; /**< adresse du sous-arbre gauche */
  struct noeudAVL* fd; /**< adresse du sous-arbre droit */
  int h; /**< hauteur du noeud : = 0 si pas de fils, 
	    sinon = 1+ max ( h du ss-arbre gauche, h du ss-arbre droit)
	 */
}NoeudAVL;

/**
   \brief définition d'un AVL
 */
typedef NoeudAVL* AVL;


/**
   \brief crée un arbre vide
   \return l'arbre vide créé
*/
AVL creerArbreVide();

/**
   \brief indique si l'arbre a est vide
   \return VRAI si l'arbre est vide, FAUX sinon
*/
Booleen estArbreVide(AVL a);

/**
   \brief insère en feuille
   \param pta l'adresse de l'AVL à modifier
   \param val la valeur à insérer dans l'AVL
*/
void insererEquilibre(AVL* pta, int val);

/** 
    \brief vide l'AVL en libérant la mémoire
    \param pta l'adresse de l'AVL à modifier
*/
void viderArbre(AVL* pta);


/** 
    \brief affiche les valeurs de l'AVL en liste croissante 
    \param a l'AVL dont on souhaite afficher les valeurs
*/
void afficherCroissant(AVL a);

/** 
    \brief affiche les valeurs de l'AVL en liste décroissante
    \param a l'AVL dont on souhaite afficher les valeurs
*/
void afficherDecroissant(AVL a);


/**
   \brief affiche l'AVL dessiné couché
    \param a l'AVL à afficher
*/
void afficherCouche(AVL a);


/**
   \brief recherche et indique si la valeur passée en paramètre 
        est dans l'AVL ou pas
    \param a l'AVL dans lequel on souhaite effectuer la recherche
    \param val la valeur cherchée
    \return VRAI si la valeur est dans l'AVL, FAUX sinon
*/ 
Booleen rechercherVal(AVL a, int val);


/**
   \brief supprime la première occurrence de la valeur dans l'arbre 
           si la valeur y est, ou ne fait rien si elle n'y est pas
   \param pta l'adresse de l'AVL à modifier
   \param val la valeur à supprimer dans l'AVL
*/
Booleen supprimerVal(AVL *pta, int val);

#endif // AVL_EXO2_H
