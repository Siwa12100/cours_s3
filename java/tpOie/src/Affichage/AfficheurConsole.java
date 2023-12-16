package Affichage;

import modele.Case;
import modele.Pion;
import modele.Plateau;

public class AfficheurConsole {

    public void afficherPlateau(Plateau p) {

        for (Case c : p.getlCases()) {
            System.out.print("Case n." + c.getId() + " : ");
            if (c.isPresent() == true) {
                System.out.println("present");
            } else {
                System.out.println("vide");
            }
        }
    }
}
