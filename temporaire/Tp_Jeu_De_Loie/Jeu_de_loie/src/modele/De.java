package modele;

import javafx.beans.property.SimpleIntegerProperty;

public abstract class De {




    protected SimpleIntegerProperty val = new SimpleIntegerProperty();

    public De(){}

    public int getVal() {
        return val.get();
    }

    protected void setVal(int val) {
        this.val.set(val);
    }

    public SimpleIntegerProperty valProperty() {
        return val;
    }
}
