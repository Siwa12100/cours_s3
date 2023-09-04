#include "struct.h"

// int main() {

//     Bibliotheque b1;
//     // utilisationBiblio();
//     // initialisationBiblio(&b1);
//     // affichageCoordonnees();
//     utilisationCoordonnees();

//     return 0;
// }

void utilisationCoordonnees() {

    Coordonnee tab [4];
    tab[0] = Nord;
    tab[1] = Sud;
    tab[2] = Est;
    tab[3] = Ouest;

    for (int i = 0; i < 4; i++) {
        printf("\n - ");
        affichageCoordonnees(tab[i]);
    }
}

void affichageCoordonnees(Coordonnee c) {

    switch (c) {

        case Nord : 
            printf("Nord");
            break;

        case Sud : 
            printf("Sud");
            break;
        
        case Est : 
            printf("Est");
            break;

        case Ouest :
            printf("Ouest");
            break;
    
        default:
            break;
    }
}

void utilisationBiblio() {

    struct Bibliotheque b1;
    strcpy(b1.etagere_1, "livre1");
    strcpy(b1.etagere_2, "livre2");
    strcpy(b1.etagere_3, "livre3");

    Bibliotheque b2;
    strcpy(b2.etagere_1, "roman1");
    strcpy(b2.etagere_2, "roman2");
    strcpy(b2.etagere_3, "roman3");
}

void initialisationBiblio(Bibliotheque * b) {

    strcpy((*b).etagere_1, "bouquin1");
    strcpy(b -> etagere_2, "bouquin2");
    strcpy(b -> etagere_3, "bouquin3");
}