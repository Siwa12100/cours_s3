package dataManagement;

import modele.Vehicule;
import modele.Vehiculetheque;

import javax.swing.tree.VariableHeightLayoutCache;
import java.io.*;
import java.util.List;

public class VehiculesDeserialiser {

    private ObjectInputStream deserialiser;

    public VehiculesDeserialiser(StringBuilder chemin) throws IOException {
        this.deserialiser = new ObjectInputStream(new FileInputStream(String.valueOf(chemin)));
    }

    public Vehiculetheque deserialiserVehiculetheque() {

        Vehiculetheque v = null;
        try {
            v = (Vehiculetheque) this.deserialiser.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println(" --> Erreur dans le deserialisation de vehiculetheque....\n\n");
            e.printStackTrace();
        }
        return v;
    }

    public Vehicule deserialiserVehicule() {

        Vehicule v = null;
        try {
            v = (Vehicule) deserialiser.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return v;
    }

    public List<Vehicule> deserialiserListeVehicules() {

        List<Vehicule> l = null;
        try {
            l = (List<Vehicule>) deserialiser.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return l;
    }
}


