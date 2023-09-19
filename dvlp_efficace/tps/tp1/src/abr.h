#ifndef def_abr_h
#define def_abr_h

/**
 * \file abr.h
 * \brief Header contenant structs & fonctions sur les arbres binaires
 * \author Jean Marcillac
 * \date 19/09/2023
 *
 * Ce fichier contient les structures des arbres binaires, des arbres binaires de recherche et de leurs nœuds,
 * ainsi qu'un enum servant à représenter des booléens.
 * Il contient aussi tous les prototypes des fonctions de l'exercice 1 du TP, sur les arbres binaires.
 */

/**
 * \struct Noeud
 * \brief Structure représentant un nœud d'un arbre binaire.
 */
typedef struct noeud {
    int h;
    int val; /**< Valeur stockée dans le nœud. */
    struct noeud *fg; /**< Pointeur vers le sous-arbre gauche. */
    struct noeud *fd; /**< Pointeur vers le sous-arbre droit. */
} Noeud;

/**
 * \typedef ArbreBin
 * \brief Type de données représentant un arbre binaire.
 */
typedef Noeud * ArbreBin;

/**
 * \typedef Abr
 * \brief Type de données représentant un arbre binaire de recherche.
 */
typedef ArbreBin Abr;

/**
 * \enum Booleen
 * \brief Énumération représentant des valeurs booléennes.
 */
typedef enum booleen {
    FAUX, /**< Valeur représentant faux. */
    VRAI /**< Valeur représentant vrai. */
} Booleen;

/**
 * \brief Crée un arbre binaire vide.
 * \return La valeur NULL
 */
ArbreBin creerArbreVide();

/**
 * \brief Vérifie si un arbre binaire est vide ou non.
 * \param b L'arbre binaire à vérifier.
 * \return VRAI si l'arbre est vide, FAUX sinon.
 */
Booleen estArbreVide(ArbreBin b);

/**
 * \brief Insère une valeur en tant que feuille dans un arbre binaire de recherche.
 * \param pta Pointeur vers l'arbre binaire de recherche.
 * \param val La valeur à insérer.
 */
void insererEnFeuille(Abr *pta, int val);

/**
 * \brief Crée un nœud contenant une valeur donnée.
 * \param val La valeur à stocker dans le nœud.
 * \return Le nœud créé.
 */
Noeud *creerNoeud(int val);

/**
 * \brief Vide un arbre binaire.
 * \param pta Pointeur vers l'arbre binaire à vider.
 */
void viderArbre(ArbreBin *pta);

/**
 * \brief Affiche les valeurs d'un arbre binaire en ordre croissant.
 * \param b L'arbre binaire à afficher.
 */
void afficherCroissant(Abr b);

/**
 * \brief Affiche les valeurs d'un arbre binaire en ordre décroissant.
 * \param b L'arbre binaire à afficher.
 */
void afficherDecroissant(Abr b);

/**
 * \brief Affiche un arbre binaire de manière graphique par couches.
 * \param a L'arbre binaire à afficher.
 */
void afficherCouche(ArbreBin a);

/**
 * \brief Supprime une valeur donnée d'un arbre binaire de recherche.
 * \param pta Pointeur vers l'arbre binaire de recherche.
 * \param val La valeur à supprimer.
 * \return VRAI si la valeur a été supprimée avec succès, FAUX sinon.
 */
Booleen supprimerVal(Abr *pta, int val);

/**
 * \brief Recherche une valeur donnée dans un arbre binaire de recherche.
 * \param a L'arbre binaire de recherche.
 * \param val La valeur à rechercher.
 * \return VRAI si la valeur est trouvée, FAUX sinon.
 */
Booleen rechercherVal(Abr a, int val);

#endif
