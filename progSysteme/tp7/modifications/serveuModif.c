#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>     /* pour read(2)/write(2) */
 
#include <netdb.h>      
#include <string.h>     /* pour memset */
 
#include <ctype.h>      /* pour toupper */
 
#include <arpa/inet.h>  /* pour inet_ntop */
 
#define REQUEST_MAX 1024  /* taille MAX en réception */
 
void usage() {
  fprintf(stderr,"usage : serveur port\n"); 
  exit(1);
}

int main(int argc, char **argv) {
  int s, sock, ret;
 
  struct addrinfo hints, *result;
 
  struct sockaddr_storage src_addr;
  socklen_t len_src_addr;
 
  char request[REQUEST_MAX];
 
  /* Vérification des arguments */
  if(argc!=2) {
    fprintf(stderr,"Erreur : Nb args !\n");
    usage();
  }

    memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_flags = AI_PASSIVE; /* Equiv INADDR_ANY */
  hints.ai_family = AF_INET6; /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* Flux => TCP */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
 
  ret = getaddrinfo(NULL, argv[1], &hints, &result);
  if (ret != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
    exit(EXIT_FAILURE);
  }

    /* Création de la socket IPv4/IPv6 */
  if((s=socket(result->ai_family, result->ai_socktype,
          result->ai_protocol))==-1) {
    perror("socket"); exit(1);
  }
 
  /* Attachement de la socket */
 
  if (bind(s, result->ai_addr, result->ai_addrlen) == -1) {
    perror("bind"); exit(1);
  }
 
  freeaddrinfo(result);
 
  /* définition de la taille de la file d'attente */
 
  if(listen(s, 5)) {
    perror("listen"); exit(1);
  }

    while(1) { /* boucle du serveur */
 
    /* Attente d'une connexion */
 
    puts("En attente de connexion...");
 
    len_src_addr=sizeof src_addr;
    if((sock=accept(s, (struct sockaddr *)&src_addr, 
      &len_src_addr))==-1) {
        perror("accept"); exit(1);
    }
 
    puts("Connexion acceptée !");

        /* boucle de traitement du client */
 
    while((ret=recv(sock, request, REQUEST_MAX,0))>0) {
 
      request[ret]=0;
 
      /* traitement de la requête(passage en majuscule) */
      {
        int i=0;
 
        while(request[i]) {
          request[i]=toupper(request[i]);
          ++i;
        }
      }

            /* Émission de la réponse */
 
      if(send(sock, request, strlen(request)+1,0) != 
          strlen(request)+1) {
        perror("send"); exit(1);
      }	
    }    /* fin de la boucle de traitement du client */
 
    if(close(sock)==-1) {
      perror("close"); exit(1);
    }
 
    fprintf(stderr, "Fin de connexion !\n");
    if(ret==-1) {
      perror("recv");
    }
 
  } /* fin boucle principale du serveur */
 
  return 0;
}


  