package dataManagement;

import modele.Vehicule;
import modele.Vehiculetheque;

import javax.swing.tree.VariableHeightLayoutCache;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.List;

public class VehiculesSerialiser {

    private ObjectOutputStream serialiser;

    public VehiculesSerialiser(StringBuilder chemin) throws IOException {

        this.serialiser = new ObjectOutputStream(new FileOutputStream(String.valueOf(new StringBuilder(chemin))));
    }

    public void serialiserListeVehicules(List<Vehicule> lVehicules) {

        try {
            this.serialiser.writeObject(lVehicules);
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void serialiserVehiculetheque(Vehiculetheque v) {
        try {
            this.serialiser.writeObject(v);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void serialiserVehicule(Vehicule v) {
        try {
            this.serialiser.writeObject(v);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
