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

    public List<Animal> getAnimaux() {
        return this.lAnimaux;
    }

    public void afficherAnimaux() {
        afficheur.afficherAnimaux(lAnimaux);
    }

    public void saisirAnimal() {

        lAnimaux.add(saisisseur.saisirAnimal());
    }


}
