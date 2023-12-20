package modele;

import java.util.ArrayList;
import java.util.List;

public class GestionnaireJoueurs {

    private List<Joueur> lJoueurs;
    private int nbJoueurs;
    private int joueurCourant;
    private int joueurSuivant;

    GestionnaireJoueurs(int nbJoueurs) {

        lJoueurs = new ArrayList<Joueur>();
        for (int i = 0; i < nbJoueurs; i ++) {
            Joueur j = new Joueur(i);
            lJoueurs.add(j);
        }

        this.joueurCourant = 0;
        this.joueurSuivant = joueurCourant + 1;

        System.out.println("Fin cTor gestJoueurs : ");
        for (Joueur j: this.lJoueurs) {
            System.out.println("------> " + j);
        }

    }

    public Joueur getJoueur(int id) {
        for (Joueur j : this.lJoueurs) {
            if (j.getId() == id) {
                return j;
            }
        }
        return null;
    }

    public int getValeurPlusGrande() {
        int val = 0;
        for (Joueur j : this.lJoueurs) {
            if (j.getIndice() >= val) {
                val = j.getIndice();
            }
        }
        return val;
    }

    public Joueur getJoueurCourant() {
        for (Joueur j: this.lJoueurs) {
            if (j.getId() == this.joueurCourant) {
                return j;
            }
        }

        return null;
    }

    public void passerJoueurSuivant() {
        this.joueurCourant = this.joueurSuivant;
        this.joueurSuivant = joueurSuivant + 1;

        if (this.joueurSuivant >= this.nbJoueurs) {
            this.joueurSuivant = 0;
        }
    }
}
