package modele;

public abstract class Vehicule {

    protected StringBuilder nom;
    protected StringBuilder marque;
    protected int id;

    protected Vehicule(int id, StringBuilder nom, StringBuilder marque) {
        this.id = id;
        this.nom = new StringBuilder(nom);
        this.marque = new StringBuilder(marque);
    }

    public StringBuilder getNom() {
        return this.nom;
    }

    public StringBuilder getMarque() {
        return this.marque;
    }

    public int getId() {
        return this.id;
    }
}
