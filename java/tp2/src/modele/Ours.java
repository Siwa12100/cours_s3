package modele;
import modele.AnimalFourrure;

public class Ours extends AnimalFourrure {

    private int poids;

    public Ours(int id, int age, StringBuilder nom, int densitePoils, int poids) {
        super(id, age, nom, densitePoils);
        this.poids = poids;
    }

    public String toString() {

        return "Ours : " + nom + " ( id : " + id + " ; age : " +
                age + " ; densiteFourure : " + densiteFourrure + " ; poids " + poids + " ).";
    }
}