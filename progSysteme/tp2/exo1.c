#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <errno.h>
#include <wait.h>



void showFileInfos(char * filename) {

	struct stat st;

	if (stat(filename, &st) ==-1){
		perror("pb avec stat");
		exit(errno);
	}

	printf("\n --> Le nom du fichier est : %s \n", filename);
	printf("\n --> La taille du fichier est : %lld octets \n", (long long) st.st_size);
	printf("\n --> La derniere date de modification est : %lld \n", (long long) st.st_mtime);
	printf("\n");
}


int main(int argc, char ** argv){

	struct stat sb;

	if (argc != 2) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

    if (lstat(argv[1], &sb) == -1) {
               perror("lstat");
               exit(EXIT_FAILURE);
    }

    showFileInfos(argv[1]); // on affiche les informations sur le fichier...

	return 0;
}