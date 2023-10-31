package modele;

public abstract class Oiseau extends Animal {

    protected int nbPlumes;
    protected Position position;

    protected Oiseau(int id, int age, StringBuilder nom, int nbPlumes) {
        super(id, age, new StringBuilder(nom));
        this.nbPlumes = nbPlumes;
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
        }
    }

    @Override
    protected adap
}
