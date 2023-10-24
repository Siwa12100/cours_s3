#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// utilisé pour l'appel des pipes
#include <unistd.h>
#include <wait.h>

#define TAILLE_BUFFER 1024

/*
    L'exo est juste ! 
*/

void codeDuFils(int tube[2]);
void codeDuPere(int tube[2]);

int main(int argc, char ** argv){
    
    int tube[2];

    if (pipe(tube) == -1){
        perror("[Erreur] : Soucis avec un pipe.");
        exit(errno);
    }

    switch (fork()){

        case -1 : 
            perror("fork");
            exit(errno);

        case 0 : // On est dans le cas du processus fils 
            close(tube[1]);
            codeDuFils(tube);
            exit(0);

        default : // On est dans le cas du processus père
            close(tube[0]);
            codeDuPere(tube);
    }

    // ------
    return 0;
}

void codeDuFils(int tube[2]) {

    char buffer[TAILLE_BUFFER];
    int cpt = 1;

    while(read(tube[0], buffer, TAILLE_BUFFER)) {
        printf("%d - fils(%d) : %s\n", cpt, strlen(buffer), buffer);
        cpt = cpt + 1;
    }

    // La fermeture du tube...
    close(tube[0]);
    exit(0);
}

void codeDuPere(int tube[2]) {

    char buffer[TAILLE_BUFFER];

    while (fgets(buffer, TAILLE_BUFFER, stdin) != NULL){
        write(tube[1], buffer, TAILLE_BUFFER);
        
    }

    // la fermeture du tube...
    close(tube[1]);
    wait(NULL);
    exit(0);
}