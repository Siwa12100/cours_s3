package modele.actions;

import modele.joueurs.Joueur;

public class ActionVide implements IAction {

    @Override
    public void activer(Joueur joueur) {
        // ne fait rien...
    }
}
