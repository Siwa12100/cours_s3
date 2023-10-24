#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_BUF 1024

int main(void){

    char buffer[TAILLE_BUF];
    // fgets(buffer, TAILLE_BUF, stdin);

    // printf("[Brouillon] : Buffer -> %s \n", buffer);

    fgets(buffer, TAILLE_BUF, stdin);
    while (buffer != NULL){
        printf("[Brouillon] : Contenu du buffer (taille : %d)-> %s \n", strlen(buffer), buffer);
        fgets(buffer, TAILLE_BUF, stdin);
    }

    return 0;
}