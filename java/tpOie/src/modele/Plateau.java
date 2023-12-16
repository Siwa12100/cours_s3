package modele;

import java.util.ArrayList;
import java.util.List;

public class Plateau {

    private List<Case> lCases;

    public Plateau() {
        this.lCases = new ArrayList<>();
    }

    public List<Case> getlCases() {
        return this.lCases;
    }

    public int getNbCases() {
        return this.lCases.size();
    }

    public void ajouterCase(Case c) {
        this.lCases.add(c);
        c.setId(this.lCases.indexOf(c));
        // System.out.println("[Temp] : case ajoutée id : " + c.getId() + " ; " + this.lCases.indexOf(c));
    }
}
