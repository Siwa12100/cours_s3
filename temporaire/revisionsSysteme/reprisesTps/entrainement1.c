#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char * argv[]) {

    if (argc != 2) {
        printf("\n Pas le bon nombre de paramètres de passés au programme...\n");
        exit(EXIT_FAILURE);
    }

    int nb = atoi(argv[1]);

    pid_t child = fork();
    int etat;
    int pidFils;

    switch(child) {

        case -1 : 
            perror("Erreur fork");
            exit(errno);
    
        case 0 :

            for (int i = 0; i < 15; i++) {

                printf("[Fils (%d)] : %d \n", nb, i);
            }
            exit(6);
            break;


        default : 

            pidFils = wait(&etat);

            if (!WIFEXITED(etat)) {

                printf("Soucis lors de la mort du fils...\n"); 
                exit(errno);
            }
            else {
                printf("\n ---> Le fils de pid %d s'est terminé avec le code %d \n\n", pidFils,  WEXITSTATUS(etat));
            }

            printf("\n ---> Fils du processus père de pid : %d \n\n", getpid());    
            system("ps");        
    }

    return 0;
}