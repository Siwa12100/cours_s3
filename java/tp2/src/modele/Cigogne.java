package modele;

public class Cigogne extends Oiseau{

    private final int longueurBec;

    public Cigogne(int id, int age, StringBuilder nom, int nbPlumes, int numSaison, int longueurBec) {
        super(id, age, new StringBuilder(nom), nbPlumes, numSaison);
        this.longueurBec = longueurBec;
    }

    public String toString() {
        return "Cigogne : " + nom + " ( id : " + id + " ; age : " +
                age + " ; nombre plumes : " + this.nbPlumes + " ; longueur bec : " + this.longueurBec
                + " ; en hivernation : " + enHibernation + " ; Position geo. : " + this.position + " ).";
    }
}
