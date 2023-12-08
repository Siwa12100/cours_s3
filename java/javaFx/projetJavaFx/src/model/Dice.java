package model;

import java.util.Random;

public class Dice {
    private static final Random RANDOM = new Random();
    private static final int NB_FACES_DEFAULT = 6;

    private final int nbFaces;
    private int value;

    public Dice(int nbFaces) {
        this.nbFaces = nbFaces;
    }

    public Dice() {
        this(NB_FACES_DEFAULT);
    }

    public int getValue() throws IllegalAccessException {
        if (value == 0)
            throw new IllegalAccessException("The dice must be rolled first.");
        return value;
    }

    public int roll() {
        return value = RANDOM.nextInt(nbFaces) + 1;
    }

    public void clear() {
        value = 0;
    }
}
