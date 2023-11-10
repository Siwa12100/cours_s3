package dataManagement;

import modele.Vehicule;
import modele.Voiture;

import java.util.ArrayList;
import java.util.List;

public class stubVehicules {

    private List<Vehicule> lVehicules;

    public stubVehicules() {
        this.lVehicules = new ArrayList<>();
    }

    public List<Vehicule> chargerVehicules() {

        Vehicule v1 = new Voiture(1, new StringBuilder("V1"), new StringBuilder("M1"), 4);
        Vehicule v2 = new Voiture(1, new StringBuilder("V2"), new StringBuilder("M2"), 6);
        Vehicule v3 = new Voiture(1, new StringBuilder("V3"), new StringBuilder("M3"), 8);
        Vehicule v4 = new Voiture(1, new StringBuilder("V4"), new StringBuilder("M4"), 4);
        lVehicules.add(v1);
        lVehicules.add(v2);
        lVehicules.add(v3);
        lVehicules.add(v4);

        return lVehicules;
    }
}
