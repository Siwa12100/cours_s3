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

#endif 