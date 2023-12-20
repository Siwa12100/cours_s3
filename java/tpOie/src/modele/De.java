package modele;

import java.util.Random;

public class De implements IFabriqueValeurAleatoire{

    private Random generateur;
    private int nbFaces;
    @Override
    public int getValeurAleatoire(int valMin, int valMax) {
        return generateur.nextInt(valMin, valMax);
    }

    public De(int nbFaces) {
        this.nbFaces = nbFaces;
        this.generateur = new Random();
    }
}
