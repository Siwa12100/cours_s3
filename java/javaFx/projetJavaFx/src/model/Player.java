package model;

public class Player {
    private static final String BASE_PLAYER_NAME_DEFAULT = "Player ";
    private static int num = 0;

    private String name;
    private int totalScore;
    private int currentScore;

    public Player(String name) {
        setName(name);
    }

    public Player() {
        this(BASE_PLAYER_NAME_DEFAULT + ++num);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getTotalScore() {
        return totalScore;
    }

    public void setTotalScore(int score) {
        totalScore = score;
    }

    public int getCurrentScore() {
        return currentScore;
    }

    public void setCurrentScore(int score) {
        currentScore = score;
    }

    @Override
    public String toString() {
        return name + " (" + totalScore + ") has currently " + currentScore;
    }
}
