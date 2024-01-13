package modele.plateau;

import Infos.AfficheurInfos;
import modele.joueurs.Joueur;

public class Case {

    private Joueur joueur;
    private boolean possedeJoueur;

    public Case() {
        this.possedeJoueur = false;
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
