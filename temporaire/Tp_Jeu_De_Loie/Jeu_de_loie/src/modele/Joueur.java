package modele;

import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleObjectProperty;

public class Joueur {



    private SimpleIntegerProperty id = new SimpleIntegerProperty();

    private ObjectProperty<Case> currentCase = new SimpleObjectProperty<>();
    public Joueur(int id) {
         setId(id);
    }

    public int getId() {
        return id.get();
    }

    private void setId(int id) {
        this.id.set(id);
    }
    public SimpleIntegerProperty idProperty() {
        return id;
    }


    public Case getCurrentCase() {
        return currentCase.get();
    }

    public void setCurrentCase(Case currentCase) {
        this.currentCase.set(currentCase);
        if (currentCase == null){
            return;
        }
        currentCase.setCurrentJoueur(this);
    }

    public ObjectProperty<Case> currentCaseProperty() {
        return currentCase;
    }

    @Override
    public String toString() {
        return "Joueur " + " numéro " + id;
    }
}