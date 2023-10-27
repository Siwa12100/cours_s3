package modele;
import modele.Animal;

public abstract class AnimalFourrure extends Animal {

    protected int densiteFourrure;

    protected AnimalFourrure(int id, int age, StringBuilder nom, int densiteFourrure) {
        super(id, age, nom);
        this.densiteFourrure = densiteFourrure;
    }
}