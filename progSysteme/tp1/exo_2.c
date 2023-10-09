#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

	// On exécute la commande ps 
	system("ps -f");
	printf("\n");

	// On remplace le code actuel par le ps, dont le chemin est le premier argument dans la commande 
	// est le chemin (on met juste le nom car le path le connais déjà), et les autres argument sont les 
	// arguments du ps 
	execlp("ps", "ps",  "-f", NULL);

	// du coup ne s'afichera pas car le code a été remplacé par le execlp au dessus.
	printf("\n Terminé ! \n");

	exit(0);
}

// la fonction system de la lib c est capable d'exécuter une fonction shell tout en laissant 
// le processus père vivre sa vie. 

// Si on es dans un programme et qu'on doit lancer un autre programme en continuant la première exécution, 
// on passe par la commande système. 