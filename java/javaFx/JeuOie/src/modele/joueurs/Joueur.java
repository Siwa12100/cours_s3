package modele.joueurs;

import Infos.AfficheurInfos;

public class Joueur {

    private StringBuilder pseudo;
    private int position;

    public Joueur(StringBuilder pseudo) {
        this.pseudo = pseudo;
        this.position = -1;
    }

    public int getPosition() {
        return this.position;
    }

    public void setPosition(int val) {
        this.position = val;
    }

    public StringBuilder getPseudo() {
        return this.pseudo;
    }

    public void setPseudo(StringBuilder val) {
        this.pseudo = val;
    }
}
