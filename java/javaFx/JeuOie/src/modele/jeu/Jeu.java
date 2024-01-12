package modele.jeu;

import Infos.AfficheurInfos;
import modele.actions.GestionnaireActions;
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
    private GestionnaireActions gestionnaireActions;

    public Jeu(JoueursManager joueursManager, IDe de, Plateau plateau) {
        this.joueursManager = joueursManager;
        this.plateau = plateau;
        this.gestionnaireActions = new GestionnaireActions(this);

        this.gestionnaireActions.initialiserActions(this.plateau);

        this.deplaceurJoueurs = new DeplaceurJoueurs(this.joueursManager, this.plateau, this.gestionnaireActions);
        this.de = de;
    }

    public void lancerPartie() {

        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Siwa")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Synin")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Senu")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Henri")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Louis")));
        this.joueursManager.ajouterJoueur(new Joueur(new StringBuilder("Jules")));

        while (!this.verifSiVainqueur()) {

            this.passerJoueurSuivant();

            int valeurDe = this.lancerDe();

            this.deplacerJoueurCourant(valeurDe);

            AfficheurInfos.afficherInfo("\n" + this.plateau + "\n");
        }

        System.out.println("Le vainqueur est : " + this.plateau.getJoueurCase(this.plateau.getNbCases() - 1).getPseudo());
    }

    public void passerJoueurSuivant() {
        this.joueursManager.passerJoueurSuivant();
    }

    public int lancerDe() {
        return this.de.getValeurRandom();
    }

    public void deplacerJoueurCourant(int de) {
        this.deplaceurJoueurs.deplacerJoueurCourant(de);
    }

    public boolean verifSiVainqueur() {
        return this.plateau.isUnVainqueur();
    }

    public Plateau getPlateau() {
        return plateau;
    }

    public IDe getDe() {
        return this.de;
    }

    public DeplaceurJoueurs getDeplaceurJoueurs() {
        return deplaceurJoueurs;
    }

    public JoueursManager getJoueursManager() {
        return joueursManager;
    }
}
