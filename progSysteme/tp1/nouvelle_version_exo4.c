#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Utilisation : %s N\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "N doit être un entier positif.\n");
        return 1;
    }

    pid_t pid;
    int i, etat;
    struct timespec t;

    for (i = 0; i < N; i++) {
        switch (pid = fork()) {
            case -1: /* Oups !!! fork n'a pas marché ! */
                perror("fork");
                exit(errno);

            case 0: /* Code du fils */
                printf("[fils %d]: je suis le fils de pid %d\n", i, getpid());
                for (int j = 0; j < 10; j++) {
                    printf("[fils %d]: %d\n", i, j);
                    t.tv_sec = 0;
                    t.tv_nsec = 500000000;
                    nanosleep(&t, NULL);
                }
                exit(2);
                break;

            default: /* Code du père */
                break;
        }
    }

    for (i = 0; i < N; i++) {
        if ((pid = wait(&etat)) == -1) {
            perror("pb avec le wait");
            exit(errno);
        }
        if (WIFEXITED(etat))
            printf("[pere]: mon fils %d a retourne le code %d\n", pid, WEXITSTATUS(etat));
        else
            printf("[pere]: mon fils %d s est mal termine\n", pid);
    }

    printf("[pere]: Fin du processus pere de pid %d.\n", getpid());

    return 0;
}
