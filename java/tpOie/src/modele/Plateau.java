package modele;

import java.util.ArrayList;
import java.util.List;

public class Plateau {

    private List<Case> lCases;

    public Plateau(int nbCases) {
        this.lCases = new ArrayList<>();

        for (int i = 0; i < nbCases; i++) {
            Case c = new Case();
            this.lCases.add(c);
        }
    }

    public List<Case> getlCases() {
        return this.lCases;
    }

    public int getNbCases() {
        return this.lCases.size();
    }

    public Case getCase(int position) {
        return this.lCases.get(position);
    }

//    public void ajouterCase(Case c) {
//        this.lCases.add(c);
//        c.setJoueur(this.lCases.indexOf(c));
//        // System.out.println("[Temp] : case ajoutée id : " + c.getId() + " ; " + this.lCases.indexOf(c));
//    }
}
