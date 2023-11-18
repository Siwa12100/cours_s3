package modele;

public class Permission {

    private int user;
    private int group;
    private int other;


    public Permission(int user, int group, int other) {

        this.user = user;
        this.group = group;
        this.other = other;
    }

    public void setPermUser(int val) {
        this.user = val;
    }

    public void setPermGroup(int val) {
        this.group = val;
    }

    public void setPermOther(int val) {
        this.other = val;
    }

    public int getPermOther() {
        return this.other;
    }

    public int getPermGroup() {
        return this.group;
    }

    public int getPermUser() {
        return this.user;
    }
}
