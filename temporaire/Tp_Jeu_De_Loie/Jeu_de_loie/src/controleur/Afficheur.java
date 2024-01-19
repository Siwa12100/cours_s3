package controleur;

import launcher.Console;
import modele.Plateau;

public class Afficheur {

    Plateau plateau;
    public Afficheur(){
    }

    public void afficher(Plateau plateau){
        for (int i = 0; i < plateau.getCaseList().size();i++){
            System.out.println(plateau.getCaseList().get(i));
        }
    }

}
