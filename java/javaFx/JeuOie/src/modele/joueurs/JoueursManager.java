package modele.joueurs;

import Infos.AfficheurInfos;

import java.util.ArrayList;
import java.util.List;

public class JoueursManager {

    private List<Joueur> lesJoueurs;
    private Joueur joueurCourant;

    private int nbJoueurs;

    public JoueursManager() {
        this.lesJoueurs = new ArrayList<>();
        this.nbJoueurs = 0;
    }

    public void passerJoueurSuivant() {

        int indexJoueurCourant = this.lesJoueurs.indexOf(this.joueurCourant);

        if (indexJoueurCourant + 1 == this.lesJoueurs.size()) {
            this.joueurCourant = this.lesJoueurs.get(0);
        } else {
            this.joueurCourant = this.lesJoueurs.get(indexJoueurCourant + 1);
        }

        AfficheurInfos.afficherInfo("[Info] : Le nouveau joueur courant est mtn " + this.joueurCourant.getPseudo() + ".");
    }

    public Joueur getJoueurCourant() {
        return this.joueurCourant;
    }

    public void deplacerPositionJoueur(Joueur j) {

    }

    public void setPositionJoueur(Joueur j, int distance) {
        j.setPosition(j.getPosition() + distance);
    }

    public void ajouterJoueur(Joueur nvJoueur){
        this.lesJoueurs.add(nvJoueur);
        this.nbJoueurs = this.nbJoueurs + 1;

        AfficheurInfos.afficherInfo("[Info joueur] : Le joueur " + nvJoueur.getPseudo() + " rejoint la partie ! ");
    }

    public int getNbJoueurs() {
        return this.nbJoueurs;
    }

    public void resetJoueurs() {
        this.lesJoueurs.clear();
    }
}
