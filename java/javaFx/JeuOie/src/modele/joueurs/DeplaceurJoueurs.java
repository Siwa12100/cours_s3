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

        // Si la nouvelle distance fait déplacer le joueur hors du plateau
        if ((joueurCourant .getPosition() + distance) > plateau.getNbCases() - 1) {

            //AfficheurInfos.afficherInfo("Attention le joueur " + joueurCourant.getPseudo() + " va sortir du plateau en avancant de " + distance + "  !");
            // On la met de manière à ce que le joueur atteigne la fin du plateau

            int futureDistance = (joueurCourant.getPosition() + distance);
            int dernierIndexPlateau = plateau.getNbCases() - 1;

//            System.out.println("temp... pos + d : " + futureDistance);
//            System.out.println("Temp... p -1 : " + dernierIndexPlateau);

            distance = dernierIndexPlateau - joueurCourant.getPosition();

            //AfficheurInfos.afficherInfo("On met donc la distance à " + distance + " !");
        }

        // Si la distance fait sortir de joueur avant le début du plateau
        if (joueurCourant .getPosition() + distance < 0) {
            // On met la distance de manière à ce qu'elle le fasse revenir au départ
            distance = joueurCourant .getPosition() * (-1);
        }

        //AfficheurInfos.afficherInfo("[Info] : La distance à parcourir pour " + joueurCourant.getPseudo() + " est de " + distance);



        // Si le plateau contient déjà un joueur à la future case du joueur courant
        if (this.plateau.isCaseContientJoueur(joueurCourant.getPosition() + distance)) {

//            if (this.plateau.getJoueurCase(joueurCourant.getPosition() + distance) != null) {
//
//                AfficheurInfos.afficherInfo("[Info] : La case " + (joueurCourant.getPosition() + distance) + " contient deja un joueur qui est " +
//                        this.plateau.getJoueurCase(joueurCourant.getPosition() + distance).getPseudo());
//            }

            // on récupère le joueur, et on lui met la position du joueur courant
            Joueur joueurADeplacer = this.plateau.getJoueurCase(joueurCourant.getPosition() + distance);
            this.joueursManager.setPositionJoueur(joueurADeplacer, distance * (-1));

            // On le met là où le joueur courant été
            this.plateau.setJoueurCase(joueurADeplacer);

            //AfficheurInfos.afficherInfo("[info] : Le joueur " + joueurADeplacer.getPseudo() + " est mtn à la position " + joueurADeplacer.getPosition() + " sur le plateau.");

        } else {
            // Sinon, on retire simplement le joueur courant de son ancienne case
            if (joueurCourant.getPosition() != -1) {
                this.plateau.getCase(joueurCourant.getPosition()).retirerJoueur();
            }
        }


        // On dispose le joueur courant sur sa nouvelle case
        this.joueursManager.setPositionJoueur(joueurCourant, distance);
        this.plateau.setJoueurCase(joueurCourant);

        //AfficheurInfos.afficherInfo("[Info] : Le joueur courant " + joueurCourant.getPseudo() + " est mtn à la position " + joueurCourant.getPosition() + " sur le plateau");

        //this.joueursManager.passerJoueurSuivant();
    }
}
