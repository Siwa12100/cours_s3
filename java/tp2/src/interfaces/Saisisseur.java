package interfaces;

import java.security.CodeSigner;
import java.util.Scanner;
import modele.Saison;
import modele.Animal;
import modele.Cigogne;
import modele.Oiseau;
import modele.Perroquet;
import modele.Loup;
import modele.Ours;

public class Saisisseur {

    private Scanner scanner;
    private Saison saison;

    public Saisisseur(Saison saison) {

        scanner = new Scanner(System.in);
        this.saison = saison;
    }


    public Animal saisirAnimal() {

        System.out.println(" --> Quel type d'animal souhaitez vous saisir ?");
        System.out.println("\t - 1 : Ours");
        System.out.println("\t - 2 : Loup");
        System.out.println("\t - 3 : Perroquet");
        System.out.println("\t - 4 : Cigogne");
        int reponse = scanner.nextInt();

        Animal temp;
        switch(reponse){

            case 1 :
                System.out.println(" --> Saisie d'un ours : ");
                temp = saisirOurs();
                break;

            case 2 :
                System.out.println(" --> Saisie d'un loup : ");
                temp = saisirLoup();
                break;

            case 3 :
                System.out.println(" --> Saisie d'un perroquet : ");
                temp = saisirPerroquet();
                break;

            case 4 :
                System.out.println(" --> Saisie d'une cigogne :");
                temp = saisirCigogne();
                break;

            default :
                System.out.println("--> Cette réponse ne correspond à aucun type d'animal...");
                temp = null;
        }

        return temp;
    }

    private Cigogne saisirCigogne() {
        String nom;
        int longueurBec;
        int id;
        int age;
        int nbPlumes;
        int numSaison = saison.getNumSaison();

        System.out.print("\t - Quel est l'id de la cigogne : ");
        id = scanner.nextInt();
        System.out.print("\t - Quel est l'age de la cigogne : ");
        age = scanner.nextInt();
        scanner.nextLine(); // Simplement pour pouvoir récupérer le string ensuite...
        System.out.print("\t - Quel est le nom de la cigogne : ");
        nom = scanner.nextLine();
        System.out.print("\t - Quel est le nombre de plumes de la cigogne : ");
        nbPlumes = scanner.nextInt();
        System.out.print("\t - Quel est la longueur du bec de la cigogne : ");
        longueurBec = scanner.nextInt();

        Cigogne temp = new Cigogne(id, age, new StringBuilder(nom), nbPlumes, numSaison, longueurBec);
        System.out.println("\n --> Cigogne " + nom + "(id : " + id + ") bien créé ! \n");
        return temp;
    }
    private Perroquet saisirPerroquet() {
        String nom;
        String cri;
        int id;
        int age;
        int nbPlumes;
        int numSaison = saison.getNumSaison();

        System.out.print("\t - Quel est l'id du perroquet : ");
        id = scanner.nextInt();
        System.out.print("\t - Quel est l'age du perroquet : ");
        age = scanner.nextInt();
        scanner.nextLine(); // Simplement pour pouvoir récupérer le string ensuite...
        System.out.print("\t - Quel est le nom du perroquet : ");
        nom = scanner.nextLine();
        System.out.print("\t - Quel est le nombre de plumes du perroquet : ");
        nbPlumes = scanner.nextInt();
        scanner.nextLine(); // Simplement pour pouvoir récupérer le string ensuite...
        System.out.print("\t - Quel est le cri du perroquet : ");
        cri = scanner.nextLine();

        Perroquet temp = new Perroquet(id, age, new StringBuilder(nom), nbPlumes, numSaison, new StringBuilder(cri));
        System.out.println("\n --> Perroquet " + nom + "(id : " + id + ") bien créé ! \n");
        return temp;
    }
    private Loup saisirLoup() {
        String nom;
        int id;
        int age;
        int densite;
        int vitesse;

        System.out.print("\t - Quel est l'id du loup : ");
        id = scanner.nextInt();
        System.out.print("\t - Quel est l'age de lu loup : ");
        age = scanner.nextInt();
        scanner.nextLine(); // Simplement pour pouvoir récupérer le string ensuite...
        System.out.print("\t - Quel est le nom du loup : ");
        nom = scanner.nextLine();
        System.out.print("\t - Quel est la densité de poil du loup : ");
        densite = scanner.nextInt();
        System.out.print("\t - Quel est la vitesse du loup : ");
        vitesse = scanner.nextInt();

        Loup temp = new Loup(id, age, new StringBuilder(nom), densite, vitesse);
        System.out.println("\n --> Loup " + nom + "(id : " + id + ") bien créé ! \n");
        return temp;
    }
    private Ours saisirOurs() {

        String nom;
        int id;
        int age;
        int densite;
        int poids;

        System.out.print("\t - Quel est l'id de l'ours : ");
        id = scanner.nextInt();
        System.out.print("\t - Quel est l'age de l'ours : ");
        age = scanner.nextInt();
        scanner.nextLine(); // Simplement pour pouvoir récupérer le string ensuite...
        System.out.print("\t - Quel est le nom de l'ours : ");
        nom = scanner.nextLine();
        System.out.print("\t - Quel est la densité de poil de l'ours : ");
        densite = scanner.nextInt();
        System.out.print("\t - Quel est le poids de l'ours : ");
        poids = scanner.nextInt();

        Ours temp = new Ours(id, age, new StringBuilder(nom), densite, poids);
        System.out.println("\n --> Ours " + nom + "(id : " + id + ") bien créé ! \n");
        return temp;
    }
}
