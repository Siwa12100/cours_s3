#include "fonctions.h"
#include "liste.h"

void manipulationChainesCaracteres() {

    char mot1 [100];
    printf("\n -> Entrez un mot : ");
    scanf("%s", &mot1);
    printf("\n -> Votre mot est : %s et il fait %d caractères.", mot1, strlen(mot1));

    char mot2 [100];
    strcpy(mot2, mot1);
    printf("\n -> Mot 2 après copie de mot1 : %s ", mot2);

    strcat(mot1, mot2);
    printf(" \n -> Les 2 mots concaténés : %s \n", mot1);
}

void manipulationFichiers() {

printf("Fonction en cours de rédaction...");
}

void manipulationAllocationDynamique() {

    int * tab = NULL;
    int taille_tab = 5;

    tab = malloc (sizeof(int) * taille_tab);
    if (tab == NULL) {
        printf("\n Erreur dans l'allocation mémoire...");
        exit(0);
    }

    for (int i = 0; i < taille_tab; i++) {
        tab[i] = i * 15;
    }

    printf("\n Affichage du tableau de int dynamique : ");
    for (int i = 0; i < taille_tab; i++) {
        printf(" %d ; ", tab[i]);
    }
    printf("\n");
    free(tab);
}