package modele.joueurs;

import Infos.AfficheurInfos;
import modele.plateau.Plateau;

public class DeplaceurJoueurs {

    private JoueursManager joueursManager;
    private Plateau plateau;

    public DeplaceurJoueurs(JoueursManager joueursManager, Plateau plateau) {

        this.joueursManager = joueursManager;
        this.plateau = plateau;
    }

    public void deplacerJoueurCourant(int distance) {

        this.joueursManager.passerJoueurSuivant();
        Joueur joueurCourant = this.joueursManager.getJoueurCourant();

        AfficheurInfos.afficherInfo("[Info jeu] : " + joueurCourant.getPseudo() + " a obtenu " + distance + " en lancant le de !");

        if ((joueurCourant .getPosition() + distance) > plateau.getNbCases() - 1) {

            int futureDistance = (joueurCourant.getPosition() + distance);
            int dernierIndexPlateau = plateau.getNbCases() - 1;
            distance = dernierIndexPlateau - joueurCourant.getPosition();
        }

        if (joueurCourant .getPosition() + distance < 0) {
            distance = joueurCourant .getPosition() * (-1);
        }

        if (this.plateau.isCaseContientJoueur(joueurCourant.getPosition() + distance)) {

            Joueur joueurADeplacer = this.plateau.getJoueurCase(joueurCourant.getPosition() + distance);

            this.joueursManager.setPositionJoueur(joueurADeplacer, distance * (-1));
            this.plateau.setJoueurCase(joueurADeplacer);

        } else {

            if (joueurCourant.getPosition() != -1) {
                this.plateau.getCase(joueurCourant.getPosition()).retirerJoueur();
            }
        }

        this.joueursManager.setPositionJoueur(joueurCourant, distance);
        this.plateau.setJoueurCase(joueurCourant);
    }
}
