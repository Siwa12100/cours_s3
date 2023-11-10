package outils;

import modele.Vehicule;
import modele.Vehiculetheque;

import java.util.List;

public class Afficheur {

    public Afficheur() {

    }

    public void afficherVehicules(List<Vehicule> l) {
        for (Vehicule v : l) {
            System.out.println(v + "\n");
        }
    }
}
