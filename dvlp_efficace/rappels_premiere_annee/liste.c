#include "liste.h"
#include "fonctions.h"

void manipulationListes() {

    Livre * l = initialisationLivre("Mythes et légendes", "Introduction du livre");
    ajouterPage(l, "début de l'histoire...");
    ajouterPage(l, "présentation des personnages...");
    ajouterPage(l, "Page à supprimer...");
    supprimerPage(l);

    afficherLivre(l);
}

void ajouterPage(Livre * l, char c []) {

    if (l == NULL) {

        printf("\n Le livre passé en paramètre n'existe pas...");
        exit(0);
    }

    Page * p = malloc (sizeof(Page));
    if (p == NULL) {
        printf("\n Soucis allocation mémoire...");
        exit(0);
    }

    strcpy(p -> mot, c);
    p -> suiv = l -> debut;
    l -> debut = p;
    l -> nb_pages += 1;
}

void afficherLivre(Livre * l) {

    if (l == NULL)  {
        printf("\n Le livre passé en paramètre n'existe pas...");
        exit(0);
    }

    printf("\n Affichage du livre : %s de %d pages : ", l -> titre, l -> nb_pages);

    Page * page_actuelle = l -> debut;
    int i = 1;

    while (page_actuelle != NULL) {
        printf("\n\t - Page %d : %s", i, page_actuelle -> mot);
        i++;
        page_actuelle = page_actuelle -> suiv;
    }
    printf("\n");
}

void supprimerPage(Livre * l) {

    if (l == NULL) {
        printf("\n Le livre passé en paramètres n'existe pas...");
        exit(0);
    }

    Page * aSupprimer = l -> debut;
    l -> debut = aSupprimer -> suiv;
    free(aSupprimer);
    l -> nb_pages -= 1;
}

Livre * initialisationLivre(char titre [], char motPage []) {

    Livre * l = malloc (sizeof(Livre));
    if (l == NULL) {
        printf("\n Soucis d'allocation mémoire...");
        exit(0);
    }

    Page * p = malloc (sizeof(Page));
    if (p == NULL) {
        printf("\n Soucis d'allocation mémoire...");
        exit(0);
    }

    strcpy(l -> titre, titre);
    strcpy(p -> mot, motPage);
    p -> suiv == NULL;
    l -> debut = p;
    l -> nb_pages == 1;

    return l;
}