package modele;

import java.util.Scanner;

public class Saisisseur {

    private Scanner scanner;

    public Saisisseur() {
        scanner = new Scanner(System.in);
    }


    public Animal saisirAnimal() {

        System.out.println(" --> Quel type d'animal souhaitez vous saisir ? \n");
        System.out.println("\t - 1 : Ours");

        int reponse = scanner.nextInt();
        System.out.println("[temp] Reponse : " + reponse + "\n");

        Animal temp;
        switch(reponse){

            case 1 :
                temp = saisirOurs();
                break;

            default :
                System.out.println("--> Cette réponse ne correspond à aucun type d'animal...\n");
                temp = null;
        }

        return temp;
    }

    private Ours saisirOurs() {

        String nom;
        int id;
        int age;
        int densite;
        int poids;

        System.out.println("\n\t - Quel est l'id de l'ours : ");
        id = scanner.nextInt();
        System.out.println("\n\t - Quel est l'age de l'ours : ");
        age = scanner.nextInt();
        scanner.nextLine(); // Simplement pour pouvoir récupérer le string ensuite...
        System.out.println("\n\t - Quel est le nom de l'ours : ");
        nom = scanner.nextLine();
        System.out.println("\n\t - Quel est la densité de poil de l'ours : ");
        densite = scanner.nextInt();
        System.out.println("\n\t - Quel est le poids de l'ours : ");
        poids = scanner.nextInt();

        Ours temp = new Ours(id, age, new StringBuilder(nom), densite, poids);
        System.out.println("\n --> Ours " + nom + "(id : " + id + ") bien créé ! \n");
        return temp;
    }
}
