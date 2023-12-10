package model;

import javafx.beans.property.*;

public class Player {
    private static final String BASE_PLAYER_NAME_DEFAULT = "Player ";
    private static int num = 0;

    private String name;

    private StringProperty nameProperty;
    // =====================
    public StringProperty getNom() {
        return this.nameProperty;
    }

    private void setNameProperty(String newName) {
        this.nameProperty.set(newName);
    }

    public ReadOnlyStringProperty nameProperty() {
        return this.nameProperty;
    }
    // =====================

    private int totalScore;

    private IntegerProperty totalScoreProperty;

    private void setTotalScoreProperty(int val) {
        this.totalScoreProperty.set(val);
    }

    public ReadOnlyIntegerProperty totalScoreProperty() {
        return this.totalScoreProperty;
    }

    private int currentScore;

    public Player(String name) {
        this.nameProperty = new SimpleStringProperty(name);
        this.currentScoreProperty = new SimpleIntegerProperty(0);
        this.totalScoreProperty = new SimpleIntegerProperty(0);
        setName(name);
    }

    private IntegerProperty currentScoreProperty;

    public ReadOnlyIntegerProperty currentScoreProperty() {
        return this.currentScoreProperty;
    }

    private void setCurrentScoreProperty(int val) {
        this.currentScoreProperty.set(val);
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
        setTotalScoreProperty(score);
    }

    public int getCurrentScore() {
        return currentScore;
    }

    public void setCurrentScore(int score) {
        currentScore = score;
        setCurrentScoreProperty(score);
    }

    @Override
    public String toString() {
        return name + " (" + totalScore + ") has currently " + currentScore;
    }
}
