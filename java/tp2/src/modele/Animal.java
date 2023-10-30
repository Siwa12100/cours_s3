package modele;

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

    public int getId(){
        return this.id;
    }

    public int getAge(){
        return this.age;
    }
}
