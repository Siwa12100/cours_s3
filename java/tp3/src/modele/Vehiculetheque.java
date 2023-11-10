package modele;

import javax.swing.tree.VariableHeightLayoutCache;
import java.util.ArrayList;
import java.util.List;

public class Vehiculetheque {

    List<Vehicule> lVehicules;

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
