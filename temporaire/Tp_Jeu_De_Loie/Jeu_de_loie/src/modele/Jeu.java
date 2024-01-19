package modele;

import gestionnaire.Deplaceur;
import gestionnaire.GestionnaireJoueur;

public class Jeu {


    private Plateau plateau;

    private GestionnaireJoueur gestionnaireJoueur;
    private Joueur currentJoueur;
    private Desimple de;

    private Deplaceur deplaceur;
    public Jeu(){
        plateau = new Plateau();
        de = new Desimple();
        deplaceur = new Deplaceur();
        gestionnaireJoueur = new GestionnaireJoueur();
        //initialisation des cases du plateau
        for (int i =1; i <= 64;i++){
            plateau.addCase(i);
        }


    }
    public void jouer(){
        int val;
        val = lancerDe();
        System.out.println("Valeur dé " + val);
        if (val == 0){
            return;
        }
        CaseDeplacer(currentJoueur,val);
        currentJoueur = gestionnaireJoueur.switchCurrentPlayer();
    }

    public void CaseDeplacer(Joueur currentJoueur, int nombreDeplacement){
        System.out.println("Current Joueur = " + currentJoueur);
        deplaceur.deplacerJoueur(plateau.rechercheCase(currentJoueur.getCurrentCase(),nombreDeplacement),currentJoueur);
    }


    public int lancerDe(){
        int val;
        return de.getVal();
    }


    public Plateau getPlateau() {
        return plateau;
    }




}
