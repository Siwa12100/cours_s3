package modele;

import java.util.ArrayList;
import java.util.List;

public class Repertoire extends Fichier {

    private StringBuilder contenu;
    private List<Fichier> lFichiers;
    private int taille;

    public  Repertoire (StringBuilder nom, int permUser, int permGroup, int permOther) {

        super(nom, permUser, permGroup, permOther);
        this.taille = 0;
        //this.contenu = new StringBuilder(contenu);
        this.lFichiers = new ArrayList<>();
    }

    public int getTaille() {
        return this.taille;
    }

    public StringBuilder getContenu() {
        return this.contenu;
    }

    public boolean  ajouterRepertoire(StringBuilder nom, int permUser, int permGroup, int permOther) {
        Repertoire temp = new Repertoire(nom, permUser, permGroup, permOther);

        for (Fichier f : this.lFichiers) {
            if (f.getNom() == temp.getNom()) {
                return false;
            }
        }
        this.lFichiers.add(temp);
        taille++;
        return true;
    }

    public boolean supprimerFichier(StringBuilder nom) {

        for (Fichier f : this.lFichiers) {
            if (f.getNom() == nom) {
                this.lFichiers.remove(f);
                taille--;
                return true;
            }
        }
        return false;
    }

    public void ajouterFichierTexte(StringBuilder nom, int permUser, int permGroup, int permOther, StringBuilder contenu) {
        FichierTexte temp = new FichierTexte(nom, permUser, permGroup, permOther, contenu);
        this.lFichiers.add(temp);
    }
}
