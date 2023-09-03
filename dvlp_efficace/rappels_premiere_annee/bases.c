#include <stdio.h>
#include <stdlib.h>

void sayHello();
void affichageVariables();
void recuperationValeurs();

int main() {
    //sayHello();
    //affichageVariables();
    recuperationValeurs();

    return 0;
}

void sayHello() {
    printf("\n -> \t Hello World ! \n");
}

void affichageVariables() {
    int i = 6;
    char c = 'h';
    unsigned int u = 18782;
    long int l = 10000;
    float f = 1110;
    double d = 17.1982;
    long double ld = 19829.97371;

    // Affichage d'un int : %d
    // Mettre une valeur après le % permet de dire combien de caractères
    // au minimum sont pris pour l'affichage. 
    printf("\n -- Int : %5d \n", i);

    // Affichage d'un unsigned int : %d
    printf(" -- Unsigned int : %5d \n", u);

    // Affichage d'un long int : %d 
    printf(" -- Long int : %5d \n", l);

    // Affichage d'un float : %f 
    // Mettre une première valeur après le % pour préciser sur combien de caractères
    // au minimum écrire le float, puis rajouter une autre valeur après un point pour 
    //préciser le nombre de chiffres après la virgule. 
    printf(" -- float : %10.2f \n", f);

    // Affichage d'un double : %f
    printf(" -- Double : %10.3f \n", d);

    // Affichage d'un char : %c 
    printf(" -- Caractère : %c \n", c);
}

void recuperationValeurs() {

    int i = 0;
    float f = 0;
    double d = 0;
    char c [100];

    printf("\n --> Donner une valeur d'entier : ");
    scanf("%d", &i);

    printf("\n --> Donner une valeur de float : ");
    scanf("%f", &f);

    // Attention : On met un %ld pour récupérer un double 
    printf("\n --> Donner une valeur de double : ");
    scanf("%lf", &d);

    printf("\n --> Donner un mot : ");
    scanf("%s", &c);

    printf("\n\n Les valeurs sont : ");
    printf("\n ------------------\n\n");

    printf(" - int : %d", i);
    printf("\n - float : %f", f);
    printf("\n - double : %f", d);
    printf("\n chaine de caractères : %s \n", c);
}