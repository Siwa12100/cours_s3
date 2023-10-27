package modele;

import java.util.ArrayList;
import java.util.List;

public class Animaltheque {

    private List<Animal> lAnimaux;
    private Afficheur afficheur;

    private Saisisseur saisisseur;

    public Animaltheque() {

        lAnimaux = new ArrayList<Animal>();
        afficheur = new Afficheur();
        saisisseur = new Saisisseur();
    }

    public void afficherAnimal() {
        //afficheur.afficherAnimal(a);

        saisisseur.saisirAnimal();
    }

    //public void afficher
}
