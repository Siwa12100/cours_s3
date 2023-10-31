package modele;

public class Perroquet extends Oiseau{

    private StringBuilder cri;

    public Perroquet(int id, int age, StringBuilder nom, int nbPlumes, int numSaison, StringBuilder cri) {
        super(id, age, nom, nbPlumes, numSaison);
        this.cri = new StringBuilder(cri);
    }

    public String toString() {
        return "Perroquet : " + nom + " ( id : " + id + " ; age : " +
                age + " ; nombre plumes : " + this.nbPlumes + " ; cri : " + this.cri
                + " ; en hivernation : " + enHibernation + " ; Position geo. : " + this.position + " ).";
    }
}
