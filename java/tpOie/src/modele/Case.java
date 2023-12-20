package modele;

public class Case {

    //private boolean presence;
    private int joueur;

    public Case() {
        this.joueur = (-1);
        //this.presence = false;
    }

//    public Case(boolean presence) {
//        this.presence = presence;
//        this.id = -1;
//    }

    public boolean isOccupee() {

        if (this.joueur == (-1)) {
            return false;
        } else {
            return true;
        }
    }

//    public void setPresence(boolean val) {
//        this.presence = val;
//    }

//    public void changerPresence() {
//        this.presence = !this.presence;
//    }

    public  int getJoueur() {
        return this.joueur;
    }

    public void setJoueur(int joueur) {
        this.joueur = joueur;
    }
}
