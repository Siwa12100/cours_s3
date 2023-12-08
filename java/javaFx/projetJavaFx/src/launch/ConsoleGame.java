package launch;

import model.Game;
import model.Player;

import java.util.Scanner;

public class ConsoleGame {
    private static final String PROMPT = ", enter R to roll the dice or H to hold your score: ";
    private static final String ALLOWED_KEYS = "[rRhH]";
    private static final Scanner SCANNER = new Scanner(System.in);

    private enum Choice {ROLL, HOLD, QUIT}

    static public Choice readChoice(String playerName) {
        String line = null;
        System.out.print(playerName + PROMPT);
        while (SCANNER.hasNext()) {
            line = SCANNER.nextLine().trim();
            if (line.length() == 1 && line.matches(ALLOWED_KEYS))
                break;
            System.out.print(playerName + PROMPT);
        }

        if (line == null)
            return Choice.QUIT;
        else {
            return switch (line.charAt(0)) {
                case 'r', 'R' -> Choice.ROLL;
                case 'h', 'H' -> Choice.HOLD;
                default -> throw new IllegalStateException("impossible branch");
            };
        }
    }

    public static void main(String[] args) {
        Game teacherFight = new Game();
        teacherFight.addPlayer(new Player("Laurent"));
        teacherFight.addPlayer(new Player("Cédric"));

        System.out.println("Laurent and Cédric are about to start a dice fight !");

        while (!teacherFight.isGameOver()) {
            Player currentPlayer = teacherFight.getCurrentPlayer();
            System.out.println(currentPlayer);
            Choice choice = readChoice(currentPlayer.getName());
            switch (choice) {
                case ROLL -> {
                    teacherFight.rollDice();
                    int diceValue = 0;
                    try {
                        diceValue = teacherFight.getDiceValue();
                    } catch (IllegalAccessException e) {
                        teacherFight.rollDice();
                    }
                    System.out.println(currentPlayer.getName() + " is rolling the dice… and get a " + diceValue);
                    if (diceValue == Game.LOSE_DICE_VALUE)
                        System.out.println(currentPlayer.getName() + " loses his turn.");
                }
                case HOLD -> {
                    teacherFight.passToNextPlayer();
                    System.out.println(currentPlayer.getName() + " decides to hold his score and has now " + currentPlayer.getTotalScore());
                }
                case QUIT -> {
                    System.out.println(currentPlayer.getName() + " quits.");
                    return;
                }
            }
        }

        Player winner = teacherFight.getCurrentPlayer();
        System.out.println(winner.getName() + " wins the game !");
    }
}
