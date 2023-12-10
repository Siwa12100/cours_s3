package model;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.ReadOnlyIntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;

import java.util.ArrayList;
import java.util.List;

public class Game {
    public static final int LOSE_DICE_VALUE = 1;
    public static final int SCORE_TO_WIN = 50;

    private IntegerProperty valeurCouranteProperty;

    public IntegerProperty getValeurCouranteProperty() {
        return this.valeurCouranteProperty;
    }

    private void setValeurCouranteProperty(int val) {
        this.valeurCouranteProperty.set(val);
    }

    public ReadOnlyIntegerProperty valeurCouranteProperty() {
        return this.valeurCouranteProperty;
    }

    private final Dice dice = new Dice();

    private final List<Player> players = new ArrayList<>();
    private int currentPlayerIndex = 0;

    private boolean gameOver;

    public boolean isGameOver() {
        return gameOver;
    }

    public void addPlayer(Player player) {
        players.add(player);
    }

    public Player getCurrentPlayer() {
        return players.get(currentPlayerIndex);
    }

    public Game() {
        this.valeurCouranteProperty = new SimpleIntegerProperty(-1);
    }

    public void rollDice() {
        int rollValue = dice.roll();
        Player currentPlayer = players.get(currentPlayerIndex);

        // ===
        setValeurCouranteProperty(rollValue);
        // ===
        if (rollValue != LOSE_DICE_VALUE) {
            currentPlayer.setCurrentScore(currentPlayer.getCurrentScore() + rollValue);
        } else {
            currentPlayer.setCurrentScore(0);
            passToNextPlayer();
        }
    }

    public void passToNextPlayer() {
        if (!isGameOver()) {
            Player currentPlayer = players.get(currentPlayerIndex);
            int newTotalScore = currentPlayer.getTotalScore() + currentPlayer.getCurrentScore();
            currentPlayer.setTotalScore(newTotalScore);
            currentPlayer.setCurrentScore(0);
            if (newTotalScore >= SCORE_TO_WIN) {
                gameOver = true;
            } else {
                currentPlayerIndex = ++currentPlayerIndex % players.size();
            }
        }
    }

    public void restart() {
        dice.clear();
        players.forEach(player -> {
            player.setCurrentScore(0);
            player.setTotalScore(0);
        });
        gameOver = false;
        passToNextPlayer();
    }

    public int getDiceValue() throws IllegalAccessException {
        return dice.getValue();
    }

    public void changerValeurCourante() throws IllegalAccessException {
        this.rollDice();
        setValeurCouranteProperty(getDiceValue());
    }
}
