package modele;

import java.util.spi.AbstractResourceBundleProvider;

public abstract class Animal {

    protected int id;
    protected int age;
    protected StringBuilder nom;
    boolean enHibernation;

    protected Animal(int id, int age, StringBuilder nom) {
        this.id =id;
        this.age = age;
        this.nom =nom;
        enHibernation = false;
    }

    protected void commencerHivernation(){
        enHibernation = true;
    }

    protected void terminerHivernation(){
        enHibernation = false;
    }

    public void adapterComportementSaison(int saison) {

        switch (saison) {

            case 1 :
                commencerHivernation();
                break;

            case 2 :
                terminerHivernation();
                break;
        }
    }

    public int getId(){
        return this.id;
    }

    public int getAge(){
        return this.age;
    }
}
