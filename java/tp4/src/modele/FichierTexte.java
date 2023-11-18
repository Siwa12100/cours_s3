package modele;

import java.time.LocalTime;

public class FichierTexte extends Fichier{

    private StringBuilder contenu;

    public FichierTexte(StringBuilder nom, int permUser, int permGroup, int permOther, StringBuilder contenu) {

        super(nom, permUser, permGroup, permOther);
        this.contenu = new StringBuilder(contenu);
    }

    public void ajouterTexte(StringBuilder texte) {
        this.contenu = new StringBuilder(this.contenu  + "\n" + texte);
    }

    public String ToString() {
        return "TextFile " + this.nom + "(" + Integer.toString(this.permissions.getPermUser()) +
                Integer.toString(this.permissions.getPermGroup()) +
                Integer.toString(this.permissions.getPermOther()) + ") created on " +
                this.dateCreation + ". \n";
    }
}
