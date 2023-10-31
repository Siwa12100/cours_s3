package modele;
import modele.Animal;


public abstract class AnimalFourrure extends Animal {
    final static int CHANGEMENT_FOURRURE = 40;
    protected int densiteFourrure;

    protected AnimalFourrure(int id, int age, StringBuilder nom, int densiteFourrure) {
        super(id, age, nom);
        this.densiteFourrure = densiteFourrure;
    }

    @Override
    protected void commencerHivernation() {
        super.commencerHivernation();
        augmenterDensitePoils(CHANGEMENT_FOURRURE);
    }

    @Override
    protected void terminerHivernation() {
        super.terminerHivernation();
        diminuerDensitePoils(CHANGEMENT_FOURRURE);
    }

    private void augmenterDensitePoils(int delta) {
        densiteFourrure = densiteFourrure + delta;
    }

    private void diminuerDensitePoils(int delta) {
        densiteFourrure = densiteFourrure - delta;
        if (densiteFourrure < 0){
            densiteFourrure = 0;
        }
    }
}