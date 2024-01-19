package launcher;

import controleur.Afficheur;
import modele.Jeu;

import java.util.Scanner;

public class Console {


    public static void main(String[] args) {
        String enter;
        Jeu jeu = new Jeu();
        Afficheur afficheur = new Afficheur();
        afficheur.afficher(jeu.getPlateau());
        Scanner scanner = new Scanner(System.in);
        enter = scanner.next();

        while(enter != "c"){
            jeu.jouer();
            afficheur.afficher(jeu.getPlateau());
            enter = scanner.next();

        }
        //Saisisseur saisisseur = new Saisisseur();


    }
}
