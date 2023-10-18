#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

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
	printf(" --> La taille du fichier est : %lld octets \n", (long long) st.st_size);
	printf(" --> La derniere date de modification est : %lld \n", (long long) st.st_mtime);
	printf("\n");
}



/*void showDir(char * dirname) {

	DIR * dossier = opendir(dirname);
	struct dirent * tmp = readdir(dossier);

	char * chaineTemp = strcat(dirname, "/");
		//printf("\n [temporaire] : %s \n", chaineTemp);

	char * fichierTemp;

	while (tmp != NULL){

		fichierTemp = strcat(tmp -> d_name, "/"); 
		//printf("\n [temporaire 2] : d_name : %s    | %s \n", tmp -> d_name, fichierTemp);
		printf("\n ---> %s \n",strcat(chaineTemp, tmp -> d_name));

		showFileInfos(strcat(chaineTemp, tmp -> d_name));
		printf("\n -------\n");

		tmp = readdir(dossier);
	}

	if (closedir(dossier) != 0){
		printf("\n [erreur] : soucis de fermeture du fichier...\n");
		exit(errno);
	}

	printf("\n");
}
 */

 void showDir(char * dirname);

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





/// Correction : 


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
		showFileInfos(path);
	
		free(path);
	}


	
}
// A reprendre pour bien tout comprendre (très important....)