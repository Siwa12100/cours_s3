import modele.actions.GestionnaireActions;
import modele.de.De;
import modele.jeu.Jeu;
import modele.joueurs.DeplaceurJoueurs;
import modele.joueurs.JoueursManager;
import modele.plateau.Plateau;

public class JeuConsole {
    public static void main(String[] args) {

        Jeu jeu = new Jeu(new JoueursManager(), new De(), new Plateau(15));
        jeu.lancerPartie();
    }
}