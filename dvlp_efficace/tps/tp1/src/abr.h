#ifndef def_abr_h
#define def_abr_h

typedef struct noeud {
    int val; 
    struct noeud * fg; 
    struct noeud * fd;
}Noeud;

typedef Noeud * ArbreBin;
typedef ArbreBin Abr;

typedef enum booleen {
    FAUX, VRAI
}Booleen;

ArbreBin creerArbreVide();
Booleen estArbreVide(ArbreBin b);
void insererEnFeuille(Abr * pta, int val);
Noeud * creerNoeud(int val);
void viderArbre(ArbreBin * pta);
void afficherCroissant(Abr b);
void afficherDecroissant(Abr b);
#endif 