package controler;
import dataManagement.VehiculesDeserialiser;
import dataManagement.VehiculesSerialiser;
import dataManagement.stubVehicules;
import modele.Vehicule;
import modele.Vehiculetheque;
import outils.Afficheur;

import java.io.File;
import java.io.IOException;

public class VehiculesManager {

    private stubVehicules stub;
    private Vehiculetheque vehiculetheque;
    private Afficheur afficheur;

    private VehiculesDeserialiser deserialiser;
    private VehiculesSerialiser serialiser;

    private StringBuilder cheminEnregistrement;

    public VehiculesManager(Afficheur afficheur, StringBuilder chemin) {
        this.vehiculetheque = new Vehiculetheque();
        this.stub = new stubVehicules();
        this.afficheur = afficheur;
        this.cheminEnregistrement = new StringBuilder(chemin);

        verifExists(chemin);

        //System.out.println("Passage par ici constructeur");

        try {
            //this.deserialiser = new VehiculesDeserialiser(this.cheminEnregistrement);
            this.serialiser = new VehiculesSerialiser(this.cheminEnregistrement);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Vehiculetheque getVehiculetheque() {
        return vehiculetheque;
    }

    static void verifExists(StringBuilder cheminFichier) {
        File fichier = new File(String.valueOf(cheminFichier));

        if (!fichier.exists()) {
            try {
                fichier.createNewFile();

            } catch (IOException e) {
                System.out.println("Passage par ici Erreur ");
                e.printStackTrace();
            }
        }
    }
//
    public void sauvegarderSerial() {
        serialiser.serialiserVehiculetheque(vehiculetheque);
    }
//
//    public void chargerSerial() {
//        this.vehiculetheque = deserialiser.deserialiserVehiculetheque();
//    }

    public void chargerStub() {
        Vehiculetheque temp = new Vehiculetheque();
        temp.ajouterVehicules(stub.chargerVehicules());
        vehiculetheque = temp;
    }

    public void afficherVehicules() {
        afficheur.afficherVehicules(vehiculetheque.getlVehicules());
    }
}
