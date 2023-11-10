#include <stdio.h>
// pour sigaction 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// utilisé pour l'appel des pipes
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <wait.h>

#define TAILLE_BUFFER 1024
volatile int pid_fils = 118712;
volatile int cpt = 0;

// struct sigaction {
//     void (* sa_handler )( int );
//     void (* sa_sigaction )( int , siginfo_t * , void *);
//     sigset_t sa_mask ;
//     int sa_flags ;
// }

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

void detournementFils() {
    printf(" --> Remise de cpt à 0 \n");
    cpt = 0;
}

void codeDuFils(int tube[2]) {

    pid_fils = getpid();
    printf("[Fils] pid_fils : %d \n", pid_fils);

    int signal = SIGUSR1;
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_handler = detournementFils;
    
    if (sigaction(signal, &action, NULL)){
        perror (" Installation detournement fils "); 
        exit (1);
    }

    

    char buffer[TAILLE_BUFFER];
    //int cpt = 1;

    do {
        errno = 0;

        while(read(tube[0], buffer, TAILLE_BUFFER)) {
            printf("%d - fils(%d) : %s\n", cpt, strlen(buffer), buffer);
            cpt = cpt + 1;
        }
    } while (errno == EINTR && !feof(stdin));

    // La fermeture du tube...
    close(tube[0]);
    exit(0);
}

void detournementPere() {
    int signal = SIGUSR1;
    printf("[Père] : volatile int fils_pid : %d \n", pid_fils);
    //printf(" Père : Coucou (signal : %d ) \n", signal);

    if (kill(pid_fils, signal) == 0){
        perror("erreur dans le kill");
        exit(1);
    }    
} 

void codeDuPere(int tube[2]) {
    printf("[Père] PID du père : %d \n", getpid());
    //printf("pid_fils : %d \n", pid_fils);

    // travail sur le détournement de signal 
    int signal = SIGUSR1;
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_handler = detournementPere;
    
    if (sigaction(signal, &action, NULL)){
        perror (" Installation coucou ");
         exit (1);
    }

    char buffer[TAILLE_BUFFER];

    do {
        errno = 0;
        while (fgets(buffer, TAILLE_BUFFER, stdin) != NULL){
        write(tube[1], buffer, TAILLE_BUFFER);
        
    }
    } while (errno == EINTR && !feof(stdin));

    //printf(" ----> %s", perror);

    // la fermeture du tube...
    close(tube[1]);
    wait(NULL);
    exit(0);
}

// tant que l'erreur est un EINTR, alors on continue la boucle de lecture 