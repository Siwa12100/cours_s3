package modele;

public class Joueur {

    private int indice;
    private int id;

    public Joueur(int id) {
        this.id = id;
        this.indice = (0);

        System.out.println("[Ctor joueur ] : Création d'un joueur d'id " + this.id + " et de case/indice " + this.indice);
    }

    public int getIndice() {
        return this.indice;
    }

    public void setIndice(int val) {
        this.indice = val;
    }

    public int getId() {
        return this.id;
    }

    public void setId(int val) {
        this.id = val;
    }

    public String toString() {
        return "ID : " + this.id + " ; Case : " + this.indice;
    }
}
