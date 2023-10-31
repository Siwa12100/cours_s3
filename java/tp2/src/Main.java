import controler.Manager;
import interfaces.Afficheur;
import interfaces.Saisisseur;
import modele.*;


public class Main {

    public static void test() {

        //Animal o1 = new Ours(11, 12 , new StringBuilder("Premier ours"), 777, 150);
        //System.out.println("\n" + o1 + "\n");

        Saison saison = new Saison();
        Saisisseur saisisseur = new Saisisseur(saison);
        Afficheur afficheur = new Afficheur();
        Animaltheque zoo = new Animaltheque(saisisseur, afficheur);
        //zoo.saisirAnimal();
        zoo.saisirAnimal();
        zoo.afficherAnimaux();


        //Animal l = new Loup(111, 34, new StringBuilder("Loulou"), 300, 130);
        //System.out.println("\n" + l + "\n");
    }

    public static void main(String[] args) {
        //System.out.println("Hello world!");
        //test();
        Manager manager = new Manager();
        manager.lancement();
    }
}

/*
    Développer une application permettant à un gestionnaire de zoo de gérer les
    entrées sorties d'animaux dans son zoo.

    Il pourra à tout moment :

    - Afficher l'état (les infos) des animaux

    - En hiver, les animaux hivernent.

    - Les oiseaux (cigognes, perroquets...) migrent du nord au sud du zoo.

    - Les animaux à fourrure (ours, loups, ...) augmentent la densité de leur pellage.
 */

