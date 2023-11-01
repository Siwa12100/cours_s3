#include <stdio.h>
#include <stdlib.h>

/*
   Cet exercice affiche l'ensemble des arguments passés en paramètres 
   passés en description, puis affiche la variable PATH. 
*/

int main(int argc, char* argv[]) {
 int i = 0;

 for (i = 0; i < argc; ++i)
    printf("argument %d : %s\n", i, argv[i]);

    printf("\n -------------------------------------------\n");
    printf("\n PATH --> ");
    printf(" %s \n", getenv("PATH"));

 return 0;
}