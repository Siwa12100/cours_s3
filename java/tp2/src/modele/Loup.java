package modele;


public class Loup extends AnimalFourrure {

    private final int vitesse;

    public Loup(int id, int age, StringBuilder nom, int densitePoils, int vitesse) {
        super(id, age, nom, densitePoils);
        this.vitesse = vitesse;
    }

    public Loup() {
        super(0, 1, new StringBuilder("Loup sans nom"), 90);
        this.vitesse = 120;
    }

    public String toString() {
        return "Loup : " + nom + " ( id : " + id + " ; age : " +
                age + " ; densiteFourure : " + densiteFourrure + " ; vitesse " + vitesse
                + " ; en hivernation : " + enHibernation + " ).";
    }
}
