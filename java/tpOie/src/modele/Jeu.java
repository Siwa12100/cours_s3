package modele;

import affichage.AfficheurConsole;

import java.util.ArrayList;
import java.util.List;

public class Jeu {

    private Plateau plateau;
    private GestionnaireJoueurs gestionnaireJoueurs;
    private IFabriqueValeurAleatoire fabriqueRand;
    private AfficheurConsole afficheurConsole;

    public Jeu(int nbCases, int nbJoueurs, IFabriqueValeurAleatoire f, AfficheurConsole afficheur) {
        this.plateau = new Plateau(nbCases);
        this.gestionnaireJoueurs = new GestionnaireJoueurs(nbJoueurs);
        this.fabriqueRand = f;

        this.afficheurConsole = afficheur;
    }

    public int gererPartie() {

        boolean gagner = false;

        while (!gagner) {
            // On lance le dé
            int valeurRand = fabriqueRand.getValeurAleatoire(1, 6);

            // On vérifie que le joueur ne sorte pas du plateau
            if (valeurRand + gestionnaireJoueurs.getJoueurCourant().getId() >= plateau.getNbCases()) {
                gagner = true;
                break;
            }

            System.out.println("[Info partie] : On lance le dé, la valeur obtenue est " + valeurRand);


            // on déplace le joueur courant en fonction de la valeur du dé
            System.out.println("[Info partie] : On lance le déplacement du joueur courant d'ID " + gestionnaireJoueurs.getJoueurCourant().getId());
            this.deplacerJoueur(gestionnaireJoueurs.getJoueurCourant(), valeurRand);

            // On regarde si on a un gagnant ou pas
            System.out.println("Valeur plus grande " + gestionnaireJoueurs.getValeurPlusGrande());
            if (gestionnaireJoueurs.getValeurPlusGrande() >= plateau.getNbCases() - 1) {
                System.out.println("[Info partie] : Le joueur le plus avancé est à " + gestionnaireJoueurs.getValeurPlusGrande() + "donc on refait un tour");
                gagner = true;
            } else {
                // Partie pas encore gagnée, on prépare le joueur suivant
                gestionnaireJoueurs.passerJoueurSuivant();
                System.out.println("[Info partie] : Le joueur du prochain tour est maintenant d'ID " + gestionnaireJoueurs.getJoueurCourant());
            }
        }

        // On affiche l'id du vainqueur...
        this.afficheurConsole.afficherMessage(" -----> Le gagnant est le joueur d'ID ---> " + gestionnaireJoueurs.getJoueurCourant().getId());
        return gestionnaireJoueurs.getJoueurCourant().getId();
    }

    private void deplacerJoueur(Joueur joueurADeplacer, int nbCases) {

        System.out.println("[Info partie] : On commence à déplacer le joueur : " + joueurADeplacer);

        // On récupère la future case du joueur à déplacer
        Case futureCase = plateau.getCase(nbCases + joueurADeplacer.getIndice());
        System.out.println("[Info partie] : La future case du joueur est la case numéro " + plateau.getlCases().indexOf(futureCase));

        plateau.getlCases().get(gestionnaireJoueurs.getJoueurCourant().getId()).setJoueur(-1);

        // Si elle est occupée
        if (futureCase.isOccupee()) {
            Joueur joueurPresentSurCase = gestionnaireJoueurs.getJoueur(futureCase.getJoueur());
            System.out.println("[Info partie] : La future case est occupée par le joueur d'ID " + joueurPresentSurCase.getId() + ", on le déplace donc en arrière");

            //System.out.println("[Temp dans deplacerJoueur] : jPresentSurCase --> " + joueurPresentSurCase);
            deplacerJoueur(joueurPresentSurCase, nbCases * (-1));
        } else {
            // On met l'ancienne case du joueur à "Aucun joueur présent"
            this.plateau.getCase(gestionnaireJoueurs.getJoueurCourant().getIndice()).setJoueur(-1);
        }

//        System.out.println("Indice du joueur à modifier : " + joueurADeplacer.getIndice());
//        System.out.println("Nombre de cases à lui ajouter : " + nbCases);

        int somme = joueurADeplacer.getIndice() + nbCases;
        //System.out.println("temp ---> somme " + somme);

        joueurADeplacer.setIndice(somme);
        //System.out.println(joueurADeplacer);

        futureCase.setJoueur(joueurADeplacer.getId());

        System.out.println("[Info partie] : Le joueur " + joueurADeplacer + " a bien été déplacé sur la case " + plateau.getlCases().indexOf(futureCase) + " ayant le joueur " + futureCase.getJoueur());
    }






    // ----- Ancien code : ---------

//    private List<Joueur> lJoueurs;
//    private Joueur joueurActuel;
//
//    public Jeu() {
//
//        this.lJoueurs = new ArrayList<>();
//        this.plateau = new Plateau();
//        //ajouterPion();
//        //this.pionActuel = this.lPions.get(0);
//    }
//
//    public void ajouterPion() {
//        Joueur p = new Joueur();
//        p.setIndice(0);
//        this.lJoueurs.add(p);
//        marquerCase(0);
//    }
//
//    public void avancerPion(int val) {
//
//    }
//
//    public void marquerCase(int id) {
//
//        for (Case c : this.plateau.getlCases()) {
//            //System.out.println("dans le foreach : id : " + id + " c.getId : " + c.getId());
//            if (c.getJoueur() == id) {
//                c.setPresence(true);
//                //System.out.println("[temp] : C : " + c.isPresent());
//            }
//        }
//    }
//
//    public void demarquerCase(int indice) {
//        for (Case c : this.plateau.getlCases()) {
//            if (c.getJoueur() == indice) {
//                c.setPresence(false);
//            }
//        }
//    }
//
//    public void setPionActuel() {
//        if (this.lJoueurs.isEmpty()) {
//            ajouterPion();
//        }
//
//        this.joueurActuel = this.lJoueurs.get(0);
//    }
//
//    public void avancerPionActuel(int val) {
//
//        if (val >= this.plateau.getNbCases()) {
//            val = this.plateau.getNbCases() - 1;
//        }
//
//        int nouvellePosition = this.joueurActuel.getIndice() + val;
//
////        if (this.plateau.getlCases().get(nouvellePosition).isPresent()) {
////            chercherPion(nouvellePosition).setIndice(this.pionActuel.getIndice());
////        }
//
//        //System.out.println("passage ici");
//        this.plateau.getlCases().get(nouvellePosition).setPresence(true);
//        this.plateau.getlCases().get(joueurActuel.getIndice()).setPresence(false);
//        joueurActuel.setIndice(nouvellePosition);
//        //System.out.println("[Temp] : val : " + val + " ; nv pos : " + nouvellePosition + " ; pion actuel : " + pionActuel.getIndice());
//    }
//
//    public Joueur chercherPion(int indice) {
//
//        Joueur temp = null;
//        for (Joueur p : this.lJoueurs)  {
//            if (p.getIndice() == indice){
//                temp = p;
//            }
//        }
//        return temp;
//    }
//
//    public void setPlateau(Plateau p) {
//        this.plateau = p;
//    }
//
//    public Plateau getPlateau() {
//        return this.plateau;
//    }
}
