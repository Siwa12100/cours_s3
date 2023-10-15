#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
 

//int argc, char **argv

int main(void) {
 
       pid_t pid;
       int status = 0;

       // A changer à l'avenir 
       int nbFils = 5;
 
       pid_t * tabPid = ( pid_t *) malloc (sizeof(pid_t) * nbFils);
       if (tabPid == NULL){
          printf("\n --> Erreur d'allocation mémoire...\n\n");
          exit(1);
       }

       for (int i = 0; i < nbFils; i++){

          switch(pid=fork()) {
 
               case -1 :
                    perror("fork"); exit(errno);
 
               case  0 : 
                    // On récupère le pid du fils 
                    tabPid[i] = pid;

                    // On affiche les nombres de 1 à 9 
                    for (int i = 0; i < 10; i++){
                         usleep(500000 * (i+1));
                         printf("\n [fils] - %d", i);
                    }

                    printf("\n");
                    // On retourne le code 2 
                    exit(2);
          } 
       }


       for (int i = 0; i < nbFils; i ++){

          pid = waitpid(tabPid[i], &status);
          
          printf("\n\n Mon fils m'a renvoyé le code de retour %d", WEXITSTATUS(status));
          printf("\n Fin du processus père de pid %d.\n", getpid());
       }


       free(tabPid);
       exit(0);
}