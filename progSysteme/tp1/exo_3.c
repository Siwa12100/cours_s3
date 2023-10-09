#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
 
 // usleep(500000);

int main(int argc, char **argv) {
 
       pid_t pid;
       int status = 0;
 
       switch(pid=fork()) {
 
               case -1 :
                    perror("fork"); exit(errno);
 
               case  0 : 

                    for (int i = 0; i < 10; i++){
                         usleep(500000);
                         printf("\n [fils] - %d", i);
                    }

                    printf("\n\n");
                    system("ps -f");

                    exit(2);
 
               default : 
                    pid = wait(&status);
                    printf("\n\n Mon fils m'a renvoyé le code de retour %d", WEXITSTATUS(status));
                    printf("\n Fin du processus père de pid %d.\n", getpid());
       } 
 
       exit(0);
}

// revoir ce que fait réellement le \n : apparement, c'est aussi un signal qui explique au système 
// d'exploitation qu'il doit afficher à l'écran 
// revoir aussi le flush


// Important de bien utiliser WEXITSTATUS(status) et pas juste status....
