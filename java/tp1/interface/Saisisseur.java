package interface;

import java.util.Scanner;
import java.util.StringBuilder;

class Saisisseur {

    private Scanner scanner;

    public Saisisseur() {
        scanner = new  Scanner();
    }

    public String[] saisirPatient() {

        String[] infos = new String[2];
        System.out.println(" -> Quel est le nom du patient ?");
        infos[0] =  scanner.nextLine();

        System.out.println(" -> Quel est le prenom du patient ? ");
        infos[1] = scanner.nextLine();

        return infos;
    }
}