#ifndef def_struct
#define def_struct

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Bibliotheque Bibliotheque;
// On fais un alias "Bibliotheque" de "struct Bibliotheque"
struct Bibliotheque {

    char etagere_1 [100];
    char etagere_2 [100];
    char etagere_3 [100];
};

typedef enum Coordonnee Coordonnee;
enum Coordonnee {

    Nord, Sud, Est, Ouest
};

void utilisationBiblio();
void initialisationBiblio(Bibliotheque * b);
void affichageCoordonnees();
void utilisationCoordonnees();

#endif 