#define TAILLE 80
pid_t pid;

void codeDuPere(int tube[2]){
    char texte[TAILLE];
    do{
        while(fgets(texte,TAILLE,stdin)){
            write(tube[1],texte,TAILLE);
        }
    }while(errno==EINTR && !feof(stdin));
    close(tube[1]);
    wait(NULL);
    printf("Le pere ce termine après le fils");
    exit(EXIT_SUCCESS);
}

void codeDuFils(int tube[2]){
    char chaine[TAILLE];
    int cpt=0;
    while(read(tube[0],chaine,TAILLE)){
        printf("[Le fils %d]: %s",cpt++,chaine);
    }
    close(tube[0]);
    printf("Ce termine car fin de lecture du tube");
    exit(0);
}

void prevenirFils(int signum){
    kill(pid,signum);
}

void coucou(int signum){
    if(pid!=0){
        prevenirFils(signum);
        printf("Coucou %d %d",pid,signum);
    }
}

void detournerSignal(int signum, void (*pFonction)(int)){
    struct sigaction action,save;
    sigemptyset(&action.sa_mask);
    action.sa_handler=coucou;
    action.sa_flags=0;
    if(sigaction(signum,&action,&save)){
        perror("Installation coucou");
        exit(1);
    }
}

int main(int argc,char* argv[]){
    int tube[2];
    detournerSignal(SIGINT,coucou);
    if(pipe(tube)==-1){
        perror("Pipe: ");
        exit(errno);
    }
    switch(pid=fork()){
        case -1:
            perror("Fork :");
            exit(errno);
        case 0:
            close(tube[1]);
            codeDuFils(tube);
            exit(0);
    }
    close(tube[0]);
    codeDuPere(tube);
}