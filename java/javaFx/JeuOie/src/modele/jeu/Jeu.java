package modele.jeu;

import Infos.AfficheurInfos;
import modele.de.IDe;
import modele.joueurs.DeplaceurJoueurs;
import modele.joueurs.Joueur;
import modele.joueurs.JoueursManager;
import modele.plateau.Plateau;

public class Jeu {

    private JoueursManager joueursManager;
    private DeplaceurJoueurs deplaceurJoueurs;

    private Plateau plateau;

    private IDe de;

    public Jeu(JoueursManager joueursManager, IDe de, Plateau plateau) {
        this.joueursManager = joueursManager;
        this.plateau = plateau;
        this.deplaceurJoueurs = new DeplaceurJoueurs(this.joueursManager, this.plateau);
        this.de = de;
    }

    public void lancerPartie() {

        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Siwa")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Synin")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Senu")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Henri")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Louis")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Jules")));

        while (!this.plateau.isUnVainqueur()) {

            int distance = this.de.getValeurRandom();
            this.deplaceurJoueurs.deplacerJoueurCourant(distance);

            AfficheurInfos.afficherInfo("\n" + this.plateau + "\n");
        }

        //System.out.println("Passage à la fin !");
        System.out.println("Le vainqueur est : " + this.plateau.getJoueurCase(this.plateau.getNbCases() - 1).getPseudo());
    }
}
