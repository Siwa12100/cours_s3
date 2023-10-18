#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <unistd.h>
#include <errno.h>
#include <wait.h>



void listeDirContent(char * dirname) {

	DIR * dossier = opendir(dirname);

	struct dirent * tmp = readdir(dossier);

	while (tmp != NULL){

		printf("- %s \n", tmp -> d_name);
		tmp = readdir(dossier);
	}

	if (closedir(dossier) != 0){
		printf("\n [erreur] : soucis de fermetur du fichier...\n");
		exit(errno);
	}

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

    listeDirContent(argv[1]);
    
	return 0;
}