//gcc -Wall -pedantic -o exo1 exo1.c
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>

//exo1
int main(int argc, char* argv[])
{
	int i = 0;
	printf("Il y a %d argument\n", argc);
	for (i = 0; i < argc; ++i)
		printf("argument %d : %s\n", i, argv[i]);
		
		puts("--------------------");
		printf("PATH = %s\n", getenv("PATH"));
	return 0;
}

//exo2
int main(void)
{
	if(system("ps -f")==-1){
        perror("Probleme appel systeme");
        exit(errno);
    }
    puts("--------------------");
    puts("Avec exec:");
    //execl("/usr/bin/ps", "Vive le malibu", "-f", NULL);
    //execl("/usr/bin/ps", "ps", "-f", NULL);
	if(execlp("ps", "ps", "-f", NULL)==-1){ // fonction de recouvrement 
        perror("Probleme avec la commande exec");
        exit(errno);
    }
    printf("Je ne serais pas afficher car execlp me supprime !\n");
    exit(0);
}

//La fonctione systeme est une fonction qui permet de lancer une fonction sous shell pour lancer la commande#include <stdio.h>

//exo3
int main(void) {
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

//exo4

void showFileInfos(char *fileName)
{
        struct stat sb;

        if (lstat(fileName, &sb) == -1) {
                perror("lstat");
                exit(EXIT_FAILURE);
        }
        printf("%s %lld %lld\n", \
                fileName, (long long) sb.st_size, (long long) sb.st_mtime);
}


void listDirContent(char *dirname){
    struct dirent *entry;
    DIR *dir;
    if((dir=opendir(dirname))==NULL){
        perror("opendir"); exit(errno);
    }

    while((entry = readdir(dir))!=NULL){
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

int showDir(char *dirname){
    struct dirent *entry;
    int len=strlen(dirname); 
    DIR *dir;

    if((dir=opendir(dirname))==NULL){
        perror("opendir"); exit(errno);
    }
    

    while((entry = readdir(dir))!=NULL){
        char *path;
        if((path=malloc(len+strlen(entry->d_name)+2))==NULL){
            perror("malloc"); exit(1);
        }
        strcpy(path,dirname); strcat(path, "/"); strcat(path,entry->d_name);
        showFileInfos(path);
    }
    closedir(dir);
    return 0;
}


int main(int argc, char *argv[])
{
    int err;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    err=showDir(argv[1]);
    if(err!=0){
        perror("showDir"); exit(errno);
    }
    return 0;
}

// exo5
#define TAILLE 80

void codeDuPere(int tube[2]){
    char texte[TAILLE];
    do{
        while(fgets(texte,TAILLE,stdin)!=NULL){
            write(tube[1],texte,TAILLE);
        }
    } while(errno==EINTR && !feof(stdin));
    close(tube[1]);
    wait(NULL);
    printf("Pere se termine après son fils.\n");
    exit(EXIT_SUCCESS);
}

void codeDuFils(int tube[2]){
    char chaine[TAILLE];
    int cpt=0;
    while(read(tube[0],chaine,TAILLE)!=NULL){
        printf("[Fils %d]: %s",cpt++, chaine);
    }
    close(tube[0]);
    printf("Le fils ce termine sur fin de lecture du tube.\n");
    exit(0);
}

void prevenirFils(int signum){
    kill(pid,signum);
}

void coucou(int sig){
    prevenirFils(sig);
    printf("Coucou ,sig %d\n",sig);
}

void detournerSignal(int signum, void (*pFonction)(int)){
    struct sigaction action,save;
    sigemptyset (&action.sa_mask);
    action.sa_handler=pFonction;
    action.sa_flags=0;
    if(sigaction(signum,&action,&save)){
        perror("Installation coucou");
        exit(1);
    }
}

int main(void){
    int tube[2];
    pid_t pid;
    detournerSignal(SIGUSR1,coucou);
    if(pipe(tube)==-1){
        perror("pipe");
        exit(errno);
    }
    switch(pid=fork()){
        case -1:
            perror("erreur fork");
            exit(errno);
        case 0:
            close(tube[1]);
            codeDuFils(tube);
            exit(0);
        default:
            close(tube[0]);
            codeDuPere(tube);
    }
}


//gcc -Wall -pedantic -o exo1 exo1.c
void codeDuPere(int tube[2]){
    char texte[TAILLE];
    while(fgets(texte,TAILLE,stdin)!=NULL){
        write(tube[1],texte,TAILLE);
    }
    close(tube[1]);
    wait(NULL);
    printf("Pere se termine après son fils.\n");
    exit(EXIT_SUCCESS);
}

void codeDuFils(int tube[2]){
    char chaine[TAILLE];
    int cpt=1;
    while(read(tube[0],chaine,TAILLE)!=NULL){
        printf("[Fils %d]: %s",cpt++, chaine);
    }
    close(tube[0]);
    printf("Le fils ce termine sur fin de lecture du tube.\n");
    exit(0);
}

void coucou(int sig){
    printf("Coucou ,sig %d\n",sig);
}

int main(void){
    int tube[2];
    if(pipe(tube)==-1){
        perror("pipe");
        exit(errno);
    }
    switch(fork()){
        case -1:
            perror("erreur fork");
            exit(errno);
        case 0:
            close(tube[1]);
            codeDuFils(tube);
            exit(0);
        default:
            close(tube[0]);
            codeDuPere(tube);
    }
}
