package modele;

public class Case {

    private boolean presence;
    private int id;

    public Case() {
        this.presence = false;
    }

    public Case(boolean presence) {
        this.presence = presence;
        this.id = -1;
    }

    public boolean isPresent() {
        return this.presence;
    }

    public void setPresence(boolean val) {
        this.presence = val;
    }

    public void changerPresence() {
        this.presence = !this.presence;
    }

    public  int getId() {
        return this.id;
    }

    public void setId(int val) {
        this.id = val;
    }
}
