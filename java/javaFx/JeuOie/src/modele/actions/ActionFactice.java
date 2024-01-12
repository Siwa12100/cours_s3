package modele.actions;

import modele.joueurs.Joueur;

public class ActionFactice implements IAction {

    @Override
    public void activer(Joueur joueur) {
        System.out.println("[Action] : Message de l'action factice...");
    }
}
