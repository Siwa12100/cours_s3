import modele.*;

import javax.sound.midi.SysexMessage;


public class Main {

    public static void test() {

        Animal o1 = new Ours(11, 12 , new StringBuilder("Premier ours"), 777, 150);
        System.out.println("\n" + o1 + "\n");

        Animaltheque zoo = new Animaltheque();
        zoo.afficherAnimal();
    }
    public static void main(String[] args) {
        //System.out.println("Hello world!");
        test();
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

