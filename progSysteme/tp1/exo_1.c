#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
 int i = 0;

 for (i = 0; i < argc; ++i)
    printf("argument %d : %s\n", i, argv[i]);

    printf("\n -------------------------------------------\n");
    printf("\n PATH --> ");
    printf(" %s \n", getenv("PATH"));

 return 0;
}