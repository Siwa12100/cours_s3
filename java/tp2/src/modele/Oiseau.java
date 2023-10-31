package modele;

public abstract class Oiseau extends Animal {

    protected int nbPlumes;
    protected Position position;

    protected Oiseau(int id, int age, StringBuilder nom, int nbPlumes, int numSaison) {
        super(id, age, nom);
        this.nbPlumes = nbPlumes;
        adapterComportementSaison(numSaison);
    }

    protected void voyager(int numSaison) {

        switch (numSaison) {

            case 1 :
                position = Position.Sud;
                break;

            case 2 :
                position = Position.enVoyageVersNord;
                break;

            case 3 :
                position = Position.Nord;
                break;

            case 4 :
                position = Position.enVoyageVersSud;
                break;
        }
    }

    @Override
    public void adapterComportementSaison(int saison) {
        super.adapterComportementSaison(saison);
        voyager(saison);
    }
}
