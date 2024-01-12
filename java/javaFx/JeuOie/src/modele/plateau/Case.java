package modele.plateau;

import modele.actions.IAction;
import modele.joueurs.Joueur;

public class Case {

    private Joueur joueur;
    private boolean possedeJoueur;

    private IAction action;

    public Case(IAction action) {
        this.possedeJoueur = false;
        this.action = action;
    }

    public Case() {
        this.possedeJoueur = false;
        this.action = null;
    }

    public void setAction(IAction action) {
        this.action = action;
    }

    public IAction getAction() {
        return this.action;
    }

    public boolean contientJoueur() {
        return this.possedeJoueur;
    }

    public Joueur getJoueur() {
        return this.joueur;
    }

    public void affecterJoueur(Joueur j) {
        this.joueur = j;
        this.possedeJoueur = true;
    }

    public void retirerJoueur() {
        this.joueur = null;
        this.possedeJoueur = false;
    }
}
