package modele;

public class Voiture extends Vehicule{

    protected int nbRoues;

    public Voiture(int id, StringBuilder nom, StringBuilder marque, int nbRoues) {
        super(id, nom, marque);
        this.nbRoues = nbRoues;
    }

    public int getNbRoues() {
        return this.nbRoues;
    }

    public String toString() {
        return "Voiture (" + this.id + ") " + this.nom + "( Marque : " + this.marque + " ; nbRoues : " + this.nbRoues
                + ").";
    }
}
