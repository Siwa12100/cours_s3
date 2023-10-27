package modele;

import java.util.List;

public class Afficheur {

    public Afficheur() {}
    public static void afficherAnimal(Animal a){
        System.out.println( a + "\n");
    }

    public static void afficherAnimaux(List<Animal> lAnimaux) {
        for (Animal a : lAnimaux){
            afficherAnimal(a);
        }
    }
}
