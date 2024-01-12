package modele.actions;

import modele.actions.speciales.ActionRejouer;
import modele.jeu.Jeu;
import modele.joueurs.DeplaceurJoueurs;
import modele.joueurs.Joueur;
import modele.joueurs.JoueursManager;
import modele.plateau.Case;
import modele.plateau.Plateau;

public class GestionnaireActions {


    private Jeu jeu;

    public GestionnaireActions(Jeu jeu) {
        this.jeu = jeu;
    }
    public void executerAction(Joueur joueur) {

        IAction action = this.jeu.getPlateau().getCase(joueur.getPosition()).getAction();
        action.activer(joueur);
    }

    public void initialiserActions(Plateau plateau) {

        JoueursManager joueursManager = this.jeu.getJoueursManager();
        DeplaceurJoueurs deplaceurJoueurs = this.jeu.getDeplaceurJoueurs();

        for (int i = 0; i < plateau.getNbCases() ; i++) {

            Case c = plateau.getCase(i);
            c.setAction(new ActionVide());
            }

        plateau.getCase(3).setAction(new ActionRejouer(deplaceurJoueurs, this.jeu.getDe()));

        }
    }

