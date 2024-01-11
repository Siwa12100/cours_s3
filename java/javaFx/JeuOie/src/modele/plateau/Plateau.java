package modele.plateau;

import Infos.AfficheurInfos;
import modele.joueurs.Joueur;

import java.util.ArrayList;
import java.util.List;

public class Plateau {

    private int nbCases;

    private List<Case> lesCases;

    public Plateau(int nbCases) {
        this.nbCases = nbCases;
        if (this.nbCases < 0) {
            this.nbCases = 0;
        }

        this.lesCases = new ArrayList<>();

        for (int i = 0; i < this.nbCases; i++) {
            Case nvCase = new Case();
            this.lesCases.add(nvCase);
        }

        AfficheurInfos.afficherInfo("[Info plateau] : Un plateau de " + this.nbCases + " a ete cree !");
    }

    public String toString() {

        StringBuilder result = new StringBuilder("Plateau (nb Cases = " + this.nbCases + " ) : \n\n");

        for (int i = 0; i < nbCases; i++) {
            result.append("\t - Case ").append(i).append(" -> ");

            if (this.lesCases.get(i).contientJoueur()) {
                result.append(this.lesCases.get(i).getJoueur().getPseudo());
            } else {
                result.append("...");
            }

            result.append("\n");
        }

        return result.toString();
    }


    public Joueur getJoueurCase(int position) {
        return this.lesCases.get(position).getJoueur();
    }

    public boolean isCaseContientJoueur(int position) {
        return this.lesCases.get(position).contientJoueur();
    }

    public void setJoueurCase(Joueur nvJoueur) {

        if (nvJoueur.getPosition() == -1) {
            AfficheurInfos.afficherInfo("[info plateau] : La position du joueur " + nvJoueur.getPseudo() + " est -1 donc il repart au départ.");
            return;
        }

        this.lesCases.get(nvJoueur.getPosition()).affecterJoueur(nvJoueur);
        AfficheurInfos.afficherInfo("[Info jeu] : " + nvJoueur.getPseudo() + " est mtn a la position " + nvJoueur.getPosition() + " !");
    }

    public int getNbCases() {
        return this.nbCases;
    }

    public Case getCase(int position) {
        return this.lesCases.get(position);
    }

    public boolean isUnVainqueur() {
        return this.lesCases.get(this.nbCases - 1).contientJoueur();
    }
}
