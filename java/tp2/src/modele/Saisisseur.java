package modele;

import java.util.Scanner;

public class Saisisseur {

    private Scanner scanner;

    public Saisisseur() {
        scanner = new Scanner(System.in);
    }


    public void saisirAnimal() {

        System.out.println(" --> Quel type d'animal souhaitez vous saisir ? \n");
        System.out.println("\t - 1 : Ours");

        int reponse = scanner.nextInt();
        System.out.println("[temp] Reponse : " + reponse + "\n");

    }
}
