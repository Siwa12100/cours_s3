#ifndef def_liste
#define def_liste

typedef struct Livre Livre;
typedef struct Page Page;

struct Page {

    char mot [100];
    Page * suiv;
};

struct Livre {

    int nb_pages;
    char titre [100];
    Page * debut;
};

Livre * initialisationLivre(char titre [], char motPage []);
void ajouterPage(Livre * l, char c []);
void supprimerPage(Livre * l);
void afficherLivre(Livre * l);

#endif