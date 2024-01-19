package gestionnaire;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import modele.Joueur;

public class GestionnaireJoueur {

    private  static int index = 0;

    private ObservableList<Joueur> joueurList;
    private Joueur currentJoueur;
    private int numberPion = 1;

    public GestionnaireJoueur(){
        joueurList = FXCollections.observableArrayList();
    }
    public void ajouterJoueur(){
        Joueur p = new Joueur(numberPion);
        joueurList.add(p);
        numberPion++;
    }

    public Joueur switchCurrentPlayer(){
        index = index +1;
        index = (index)%joueurList.size();

        return currentJoueur = joueurList.get(index);
    }

    public Joueur getCurrentJoueur(){
        return currentJoueur;
    }

    public void InitaliseJoueur() {

        currentJoueur = joueurList.get(0);
    }

    public ObservableList<Joueur> getJoueurList() {
        return joueurList;
    }
}
