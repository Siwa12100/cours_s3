package modele;

import javax.swing.tree.VariableHeightLayoutCache;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Vehiculetheque implements Serializable {

    private List<Vehicule> lVehicules;

    public Vehiculetheque() {
        this.lVehicules = new ArrayList<>();
    }

    public List<Vehicule> getlVehicules() {
        return lVehicules;
    }

    public void ajouterVehicules(List<Vehicule> nvVehicules) {
        for (Vehicule v: nvVehicules) {
            this.lVehicules.add(v);
        }
    }
}
