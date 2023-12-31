package modele;
import modele.AnimalFourrure;

public class Ours extends AnimalFourrure {

    private int poids;

    public Ours(int id, int age, StringBuilder nom, int densitePoils, int poids) {
        super(id, age, nom, densitePoils);
        this.poids = poids;
    }

    public Ours() {
        super(0, 1, new StringBuilder("Ours sans nom"), 77 );
        this.densiteFourrure = 77;
    }

    public String toString() {
        return "Ours : " + nom + " ( id : " + id + " ; age : " +
                age + " ; densiteFourure : " + densiteFourrure + " ; poids " + poids
                + " ; en hivernation : " + enHibernation + " ).";
    }
}