package controler;
import dataManagement.stubVehicules;
import modele.Vehicule;
import modele.Vehiculetheque;
import outils.Afficheur;

public class VehiculesManager {

    private stubVehicules stub;
    private Vehiculetheque vehiculetheque;
    Afficheur afficheur;

    /*
    public VehiculesManager(stubVehicules stubV) {

    }
    */

    public VehiculesManager(Afficheur afficheur) {
        this.vehiculetheque = new Vehiculetheque();
        this.stub = new stubVehicules();
        this.afficheur = afficheur;

        this.vehiculetheque.ajouterVehicules(stubVehicules.);
    }

    public Vehiculetheque getVehiculetheque() {
        return vehiculetheque;
    }

    public void afficherVehicules() {
        afficheur.afficherVehicules(vehiculetheque.getlVehicules());
    }
}
