#ifndef def_avl_h
#define dev_avl_h 

/**
 * \struct Noeud
 * \brief Structure représentant un nœud d'un arbre binaire.
 */
typedef struct noeud {
    int h; /**< Hauteur maximale des sous arbres partant du noeud*/
    int val; /**< Valeur stockée dans le nœud. */
    struct noeud * fg; /**< Pointeur vers le sous-arbre gauche. */
    struct noeud * fd; /**< Pointeur vers le sous-arbre droit. */
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
typedef ArbreBin Avl;

/**
 * \enum Booleen
 * \brief Énumération représentant des valeurs booléennes.
 */
typedef enum booleen {
    FAUX, /**< Valeur représentant faux. */
    VRAI /**< Valeur représentant vrai. */
} Booleen;


// good 
void mettreAjourHauteur(Noeud * n);

// good 
ArbreBin creerArbreVide();

// good 
Booleen estArbreVide(ArbreBin b);

// good 
void insererEnFeuille(Avl * ptv, int val);

// good 
Noeud * creerNoeud(int val);

// good 
void viderArbre(ArbreBin * ptv);

// good 
void afficherCroissant(Avl v);

// good 
void afficherDecroissant(Avl v);

// good 
void afficherCouche(ArbreBin b);

// good 
void supprimerVal(Avl * pta, int val);

// good 
Booleen rechercherVal(Avl v, int val);


// Il manque : 
// - rééquilibrer 
// rotation Gauche & rotation Droite 

#endif
