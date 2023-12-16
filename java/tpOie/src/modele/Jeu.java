package modele;

import java.util.ArrayList;
import java.util.List;

public class Jeu {

    private Plateau plateau;
    private List<Pion> lPions;
    private Pion pionActuel;

    public Jeu() {

        this.lPions = new ArrayList<>();
        this.plateau = new Plateau();
        //ajouterPion();
        //this.pionActuel = this.lPions.get(0);
    }

    public void ajouterPion() {
        Pion p = new Pion();
        p.setIndice(0);
        this.lPions.add(p);
        marquerCase(0);
    }

    public void avancerPion(int val) {

    }

    public void marquerCase(int id) {

        for (Case c : this.plateau.getlCases()) {
            //System.out.println("dans le foreach : id : " + id + " c.getId : " + c.getId());
            if (c.getId() == id) {
                c.setPresence(true);
                //System.out.println("[temp] : C : " + c.isPresent());
            }
        }
    }

    public void demarquerCase(int indice) {
        for (Case c : this.plateau.getlCases()) {
            if (c.getId() == indice) {
                c.setPresence(false);
            }
        }
    }

    public void setPionActuel() {
        if (this.lPions.isEmpty()) {
            ajouterPion();
        }

        this.pionActuel = this.lPions.get(0);
    }

    public void avancerPionActuel(int val) {

        if (val >= this.plateau.getNbCases()) {
            val = this.plateau.getNbCases() - 1;
        }

        int nouvellePosition = this.pionActuel.getIndice() + val;

//        if (this.plateau.getlCases().get(nouvellePosition).isPresent()) {
//            chercherPion(nouvellePosition).setIndice(this.pionActuel.getIndice());
//        }

        //System.out.println("passage ici");
        this.plateau.getlCases().get(nouvellePosition).setPresence(true);
        this.plateau.getlCases().get(pionActuel.getIndice()).setPresence(false);
        pionActuel.setIndice(nouvellePosition);
        //System.out.println("[Temp] : val : " + val + " ; nv pos : " + nouvellePosition + " ; pion actuel : " + pionActuel.getIndice());
    }

    public Pion chercherPion(int indice) {

        Pion temp = null;
        for (Pion p : this.lPions)  {
            if (p.getIndice() == indice){
                temp = p;
            }
        }
        return temp;
    }

    public void setPlateau(Plateau p) {
        this.plateau = p;
    }

    public Plateau getPlateau() {
        return this.plateau;
    }
}
