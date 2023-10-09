/** 
    \file abr_exo1.h
    \author C. SIMON
    \date 02/07/2022
    \brief package des ABR : structure et fonctionnalités de base 
 */


#ifndef ABR_EXO1_H
#define ABR_EXO1_H


#include "pratique.h"

/**
   \brief structure de noeud pour un ABR
 */


typedef struct noeudABR{
  int val;  /**< valeur contenue dans le noeud */
  struct noeudABR* fg; /**< adresse du sous-arbre gauche */
  struct noeudABR* fd; /**< adresse du sous-arbre droit */
}NoeudABR;

/**
   \brief définition d'un ABR
 */
typedef NoeudABR* ABR;


/**
   \brief crée un arbre vide
   \return l'arbre vide créé
*/
ABR creerArbreVide();

/**
   \brief indique si l'arbre a est vide
   \return VRAI si l'arbre est vide, FAUX sinon
*/
Booleen estArbreVide(ABR a);

/**
   \brief insère en feuille
   \param pta l'adresse de l'ABR à modifier
   \param val la valeur à insérer dans l'ABR
*/
void insererEnFeuille(ABR* pta, int val);

/** 
    \brief vide l'ABR en libérant la mémoire
    \param pta l'adresse de l'ABR à modifier
*/
void viderArbre(ABR* pta);

/** 
    \brief affiche les valeurs de l'ABR en liste croissante 
    \param a l'ABR dont on souhaite afficher les valeurs
*/
void afficherCroissant(ABR a);


/** 
    \brief affiche les valeurs de l'ABR en liste décroissante
    \param a l'ABR dont on souhaite afficher les valeurs
*/
void afficherDecroissant(ABR a);

/**
   \brief affiche l'ABR dessiné couché
    \param a l'ABR à afficher
*/
void afficherCouche(ABR a);


/**
   \brief recherche et indique si la valeur passée en paramètre 
        est dans l'ABR ou pas
    \param a l'ABR dans lequel on souhaite effectuer la recherche
    \param val la valeur cherchée
    \return VRAI si la valeur est dans l'ABR, FAUX sinon
*/ 
Booleen rechercherVal(ABR a, int val);

/**
   \brief supprime la première occurrence de la valeur dans l'arbre 
           si la valeur y est, ou ne fait rien si elle n'y est pas
   \param pta l'adresse de l'ABR à modifier
   \param val la valeur à supprimer dans l'ABR
*/
Booleen supprimerVal(ABR *pta, int val);

#endif // ABR_EXO1_H
