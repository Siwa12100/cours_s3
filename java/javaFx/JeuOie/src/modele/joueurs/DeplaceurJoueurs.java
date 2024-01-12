package modele.joueurs;

import Infos.AfficheurInfos;
import modele.actions.GestionnaireActions;
import modele.plateau.Plateau;

public class DeplaceurJoueurs {

    private JoueursManager joueursManager;
    private Plateau plateau;
    private GestionnaireActions gestionnaireActions;

    public DeplaceurJoueurs(JoueursManager joueursManager, Plateau plateau, GestionnaireActions gestionnaireActions) {

        this.joueursManager = joueursManager;
        this.plateau = plateau;
        this.gestionnaireActions = gestionnaireActions;
    }

    public void deplacerJoueurCourant(int distance) {

        Joueur joueurCourant = this.joueursManager.getJoueurCourant();
        this.deplacerJoueur(joueurCourant, distance);
    }

    public void deplacerJoueur(Joueur joueur, int distance) {

        AfficheurInfos.afficherInfo("[Info jeu] : " + joueur.getPseudo() + " a obtenu " + distance + " en lancant le de !");

        if ((joueur.getPosition() + distance) > plateau.getNbCases() - 1) {

            int futureDistance = (joueur.getPosition() + distance);
            int dernierIndexPlateau = plateau.getNbCases() - 1;
            distance = dernierIndexPlateau - joueur.getPosition();
        }

        if (joueur.getPosition() + distance < 0) {
            distance = joueur .getPosition() * (-1);
        }

        if (this.plateau.isCaseContientJoueur(joueur.getPosition() + distance)) {

            Joueur joueurADeplacer = this.plateau.getJoueurCase(joueur.getPosition() + distance);

            this.joueursManager.setPositionJoueur(joueurADeplacer, distance * (-1));
            this.plateau.setJoueurCase(joueurADeplacer);

        } else {

            if (joueur.getPosition() != -1) {
                this.plateau.getCase(joueur.getPosition()).retirerJoueur();
            }
        }

        this.joueursManager.setPositionJoueur(joueur, distance);
        this.plateau.setJoueurCase(joueur);

        this.gestionnaireActions.executerAction(joueur);

    }
}
