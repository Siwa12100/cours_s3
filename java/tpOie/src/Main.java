import Affichage.AfficheurConsole;
import modele.Case;
import modele.Jeu;
import modele.Plateau;

public class Main {

    public static void tests() {
        Plateau p = new Plateau();
        AfficheurConsole afficheur = new AfficheurConsole();

        for (int i = 0; i < 10; i++) {
            p.ajouterCase(new Case());
        }

        afficheur.afficherPlateau(p);
    }

    public static void main(String[] args) {

        Jeu jeu = new Jeu();
        Plateau p = new Plateau();

        for (int i = 0; i < 10; i++) {
            p.ajouterCase(new Case());
        }

        jeu.setPlateau(p);
        jeu.ajouterPion();
        jeu.setPionActuel();
        AfficheurConsole afficheur = new AfficheurConsole();

        afficheur.afficherPlateau(jeu.getPlateau());

        jeu.avancerPionActuel(5);

        System.out.println("");
        System.out.println("");

        afficheur.afficherPlateau(jeu.getPlateau());
    }
}
