package modele;

import interfaces.Afficheur;
import interfaces.Saisisseur;

import java.util.ArrayList;
import java.util.List;

public class Animaltheque {

    private List<Animal> lAnimaux;
    private Afficheur afficheur;
    private Saisisseur saisisseur;

    public Animaltheque(Saisisseur s, Afficheur a) {

        lAnimaux = new ArrayList<Animal>();
        afficheur = a;
        saisisseur = s;
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
