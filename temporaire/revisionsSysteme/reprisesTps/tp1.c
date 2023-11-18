#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>

void  mainExo3(void) {
    pid_t pid;
	int i, etat;
	struct timespec t;
    switch(pid=fork()) {
        case -1 :// Oups !!! fork n'a pas marché !
            perror("fork"); 
            exit(errno);

        case  0 :// Code du fils
            printf("[fils]: je suis le fils de pid %d\n", getpid());
            for (i=0; i<10 ; i++) {
            printf("[fils]: %d\n",i);
            t.tv_sec=0;
            t.tv_nsec=500000000;
            nanosleep(&t,NULL);
            //usleep(500000);
            }
            system("ps -f");
            exit(2);
            break;

        default :// Code du père
            if ((pid=wait(&etat))==-1) {
				perror("pb avec le wait");
				exit(errno);
			}
			if (WIFEXITED(etat))
				printf("[pere]: mon fils %d a retourne le code %d\n", pid, WEXITSTATUS(etat));
			else
				printf("[pere]: mon fils %d s est mal termine\n",pid);
            
            printf("[pere]: Fin du processus pere de pid %d.\n", getpid());
       }

    exit(0);
}


int mainExo4Gpt(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nombre_de_fils>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int nFils = atoi(argv[1]);
    if (nFils <= 0) {
        fprintf(stderr, "Le nombre de fils doit être un entier positif.\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    int i, etat;

    for (int id = 0; id < nFils; id++) {
        switch (pid = fork()) {
            case -1: // Oups !!! fork n'a pas marché !
                perror("fork");
                exit(errno);

            case 0: // Code du fils
                printf("[fils %d]: je suis le fils de pid %d\n", id, getpid());
                for (i = 0; i < 10; i++) {
                    printf("[fils %d]: %d\n", id, i);
                    usleep(500000); // Utilisez usleep pour simplifier
                }
                exit(2);

            default:
                break;
        }
    }

    // Code du père
    for (int id = 0; id < nFils; id++) {
        if ((pid = wait(&etat)) == -1) {
            perror("pb avec le wait");
            exit(errno);
        }
        if (WIFEXITED(etat))
            printf("[pere]: mon fils %d (id %d) a retourne le code %d\n", pid, id, WEXITSTATUS(etat));
        else
            printf("[pere]: mon fils %d (id %d) s est mal termine\n", pid, id);
    }
    printf("[pere]: Fin du processus pere de pid %d.\n", getpid());

    return 0;

}

int main(int argc, char * argv[]) {
    //mainExo3();
    mainExo4Gpt(argc, argv);
}