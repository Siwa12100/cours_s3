#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <unistd.h>
#include <errno.h>
#include <wait.h>

// break : permet de sortir carrément d'une boucle 
// continue : permet de passer directement à l'itération suivante de la boucle


void showFileInfos(char * filename) {

	struct stat st;

	if (stat(filename, &st) ==-1){
		perror("pb avec stat");
		exit(errno);
	}

	printf("\n --> Le nom du fichier est : %s \n", filename);
	printf(" --> La taille du fichier est : %lld octets \n", (long long) st.st_size);
	printf(" --> La derniere date de modification est : %lld \n", (long long) st.st_mtime);
	printf("\n");
}


// fonction utilisée à la fin de showDir définie plus bas...
int inspectionPath(char * path, char * d_name, unsigned char type);

void showDir(char * dirname) {

	struct dirent * entry;
	DIR * dir;
	int len = strlen(dirname);

	if ((dir = opendir(dirname)) == NULL) {
		perror("opendir");
		exit(errno);
	}

	while ((entry = readdir(dir)) != NULL) {

		char * path;

		if ((path = malloc(len + strlen(entry -> d_name) + 2)) == NULL) {

			perror("malloc");
			exit(1);
		}

		strcpy(path, dirname); 
		strcat(path, "/");

		
		strcat(path, entry -> d_name);

		// Dans l'exo 4, on a juste à voir si ce qu'on a récupéré est un répertoire ou un fichier 
		// et agir en conséquence, plutôt que de considérer que tout est un fichier.....
		// Et dans l'exo 4, surtout ne pas traiter . et .. sinon on va boucler à l'infini....

		// la fonction inspectionPath prend en compte l'analyse nécessaire pour l'exo 4 
		switch(inspectionPath(path, entry -> d_name, entry -> d_type)) {

			default : break;

		}

		showFileInfos(path);
	
		free(path);
	}


	
}

// En fait on peut utiliser le unsigned char comme un int... (à comprendre pourquoi...)
int inspectionPath(char * path, char * d_name, unsigned char type) {


	printf("\n Path courant : %s | d_name courant : %s | type : %d", path, d_name, type);


	// on regarde si le fichier est ..
	if (strcmp(d_name, "..") == 0) return -1;
	// on regarde si le fichier est .
	if (strcmp(d_name, ".") == 0) return -1;

	// on regarde si c'est un fichier 
	if (type == 8) return 1;
	// on regarde si c'est un dossier 
	if (type == 4) return 2;


	// sinon on retourne 0...
	return 0; 
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

    showDir(argv[1]);

	return 0;
}

