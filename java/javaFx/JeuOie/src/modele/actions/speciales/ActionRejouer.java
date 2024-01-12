package modele.actions.speciales;

import Infos.AfficheurInfos;
import modele.actions.IAction;
import modele.de.IDe;
import modele.joueurs.DeplaceurJoueurs;
import modele.joueurs.Joueur;

public class ActionRejouer implements IAction {

    private DeplaceurJoueurs deplaceurJoueurs;
    private Joueur joueur;
    private IDe de;

    public ActionRejouer(DeplaceurJoueurs deplaceurJoueurs, IDe de) {
        this.deplaceurJoueurs = deplaceurJoueurs;
        this.joueur = joueur;
        this.de = de;
    }
    @Override
    public void activer(Joueur joueur) {

        AfficheurInfos.afficherInfo("[Action] : Action rejouee activee pour " + joueur.getPseudo() + " !");
        this.deplaceurJoueurs.deplacerJoueur(joueur, this.de.getValeurRandom());

    }
}
