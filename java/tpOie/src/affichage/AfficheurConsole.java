package affichage;

import modele.Case;
import modele.Plateau;

public class AfficheurConsole {

    public void afficherPlateau(Plateau p) {

        for (Case c : p.getlCases()) {
            System.out.print("Case n." + c.getJoueur() + " : ");
            if (c.isOccupee() == true) {
                System.out.println("present");
            } else {
                System.out.println("vide");
            }
        }
    }

    public void afficherMessage(String msg) {
        System.out.println("[Info] : " + msg);
    }
}
