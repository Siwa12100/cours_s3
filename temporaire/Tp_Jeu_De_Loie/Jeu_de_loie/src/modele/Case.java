package modele;

import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleObjectProperty;

public class Case {

    private ObjectProperty<Joueur> currentJoueur = new SimpleObjectProperty<>();


    private SimpleIntegerProperty num = new SimpleIntegerProperty();


    public Case(int num){
        currentJoueur.set(null);
        setNum(num);
    }

    public int getNum(){
        return num.get();
    }
    public SimpleIntegerProperty numProperty() {
        return num;
    }

    private void setNum(int num) {
        this.num.set(num);
    }

    public ObjectProperty<Joueur> currentJoueurProperty() {
        return currentJoueur;
    }
    public Joueur getCurrentJoueur() {
        return currentJoueur.get();
    }

    public void setCurrentJoueur(Joueur currentJoueur) {
        this.currentJoueur.set(currentJoueur);
    }

    @Override
    public String toString(){

        if (currentJoueur == null){

            return "Case numéro " + getNum() + " ne contient aucun pion" ;
        }
        return "Case numéro " + getNum() + " contient le pion " + getCurrentJoueur().getId() ;
    }
}
