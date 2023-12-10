package codebehind;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;

import java.net.URL;
import java.util.ResourceBundle;

import model.Game;
import model.Player;

public class Index implements Initializable {


    private Game game;
    @FXML
    public Label player1ScoreLabel;

    @FXML
    public Label scoreCourant;

    @FXML
    public Label player2ScoreLabel;

    @FXML
    public Label joueurCourant;

    @FXML
    public Label player1ScoreLabelVal;

    @FXML
    public Label player2ScoreLabelVal;

    @FXML
    public Label valCouranteTemporaire;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        this.game = new Game();

        Player p1 = new Player("Jules");
        player1ScoreLabel.textProperty().bind(p1.nameProperty().concat(" : "));
        p1.setCurrentScore(0);

        Player p2 = new Player("Louis");
        player2ScoreLabel.textProperty().bind(p2.nameProperty().concat(" : "));
        p2.setCurrentScore(0);

        player1ScoreLabelVal.textProperty().bind(p1.totalScoreProperty().asString());
        player2ScoreLabelVal.textProperty().bind(p2.totalScoreProperty().asString());

        this.game.addPlayer(p1);
        this.game.addPlayer(p2);

        joueurCourant.textProperty().bind(this.game.getCurrentPlayer().nameProperty());
        scoreCourant.textProperty().bind(this.game.valeurCouranteProperty().asString());
        valCouranteTemporaire.textProperty().bind(this.game.valeurCouranteProperty().asString());
    }

    @FXML
    public void lancerDe() throws IllegalAccessException {

//        System.out.println("Debut : Joueur " + game.getCurrentPlayer().getName() + " Sc. courant : " + game.getCurrentPlayer().getCurrentScore() +
//                " Sc. total : " + game.getCurrentPlayer().getTotalScore() + "\n");
        game.rollDice();
        joueurCourant.textProperty().unbind();
        joueurCourant.textProperty().bind(this.game.getCurrentPlayer().nameProperty());

        scoreCourant.textProperty().unbind();
        scoreCourant.textProperty().bind(game.getCurrentPlayer().currentScoreProperty().asString());

        //game.changerValeurCourante();

//        System.out.println("Fin : Joueur " + game.getCurrentPlayer().getName() + " Sc. courant : " + game.getCurrentPlayer().getCurrentScore() +
//                " Sc. total : " + game.getCurrentPlayer().getTotalScore() + "\n");
    }

    @FXML
    public void Hold() throws IllegalAccessException {
        game.passToNextPlayer();
        joueurCourant.textProperty().unbind();
        joueurCourant.textProperty().bind(this.game.getCurrentPlayer().nameProperty());
    }
}
