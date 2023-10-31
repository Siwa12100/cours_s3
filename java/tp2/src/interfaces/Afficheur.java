package interfaces;

import modele.Animal;

import java.util.List;

public class Afficheur {

    public Afficheur() {}
    public static void afficherAnimal(Animal a){

        System.out.print(a);
        System.out.println();
    }

    public static void afficherAnimaux(List<Animal> lAnimaux) {
        for (Animal a : lAnimaux){
            afficherAnimal(a);
        }
        System.out.println();
    }
}
