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
        //AfficheurInfos.afficherInfo("[info case] : Le joueur " + j.getPseudo() + " arrive mtn case " + j.getPosition());

    }

    public void retirerJoueur() {
        this.joueur = null;
        this.possedeJoueur = false;
    }
}
