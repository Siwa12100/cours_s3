#include "bibliArbres.c"

int main(void) {

    ArbreBin a = creerArbreEnracine (45, creerArbreVide(), creerArbreVide());
    //afficherCouche(a);

    for (int i = 0; i < 7; i ++){
        insererEnFeuille(&a, (i + 3) * 5);
    }

    for (int i = 16; i > 0; i --){
        insererEnFeuille(&a, (i + 3) * 5);
    }

    afficherCouche(a);
    printf("\n\n");
    
    return 0;
}