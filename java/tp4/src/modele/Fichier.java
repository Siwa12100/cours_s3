package modele;

import java.time.LocalTime;

public abstract class Fichier {

    protected StringBuilder nom;
    protected final LocalTime dateCreation;
    protected Permission permissions;

    protected Fichier(StringBuilder nom, int permUser, int permGroup, int permOther) {
        this.dateCreation = LocalTime.now();
        this.nom = new StringBuilder(nom);
        this.permissions.setPermUser(permUser);
        this.permissions.setPermGroup(permGroup);
        this.permissions.setPermOther(permOther);
    }

    public void setPermissions(int user, int group, int other) {
        this.permissions.setPermOther(other);
        this.permissions.setPermGroup(group);
        this.permissions.setPermUser(user);
    }

    public StringBuilder getNom() {
        return this.nom;
    }

    public LocalTime getDateCreation() {
        return this.dateCreation;
    }

//    public String ToString() {
//        //return
//    }
}
