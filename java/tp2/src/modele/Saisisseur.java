package modele;

import java.util.Scanner;

public class Saisisseur {

    private Scanner scanner;

    public Saisisseur() {
        scanner = new Scanner(System.in);
    }


    public Animal saisirAnimal() {

        System.out.println(" --> Quel type d'animal souhaitez vous saisir ?");
        System.out.println("\t - 1 : Ours");
        System.out.println("\t - 2 : Loup");
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

            default :
                System.out.println("--> Cette réponse ne correspond à aucun type d'animal...");
                temp = null;
        }

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
