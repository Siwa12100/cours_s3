package modele;

import gestionnaire.GestionnaireJoueur;
import javafx.beans.binding.Bindings;
import javafx.collections.ListChangeListener;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Text;

public class MainVue {

    private final int  countnbPlayer= 0 ;
    Jeu jeu ;
    Desimple deSimple = new Desimple();
    GestionnaireJoueur gestionnaireJoueur;
    Joueur currentJoueur;
    @FXML
    GridPane gridPanel;

    @FXML
    GridPane gridPlayer;
    @FXML
    Button btStart;

    @FXML
    Button addPlay;

    @FXML
    Button de;

    @FXML
    Label idValeur;

    @FXML
    Label idPlayer;

    public void initialize() {
        de.setDisable(true);
            jeu = new Jeu();
            gestionnaireJoueur = new GestionnaireJoueur();
            creationPlateau();
        gestionnaireJoueur.getJoueurList().addListener(new ListChangeListener<Joueur>() {
            @Override
            public void onChanged(Change<? extends Joueur> c) {
                while (c.next()) {
                    if (c.wasAdded()) {
                        for (Joueur joueur : c.getAddedSubList()) {
                            addGridPlayer();
                        }
                    }
                    if (c.wasUpdated()) {
                        for (Joueur joueur : c.getAddedSubList()) {
                            changeGridPlayer(joueur);
                        }
                    }
                }
            }
        });


    }

    public void creationPlateau() {
        int nombreColonnes = 16;

        for (int i = 0; i < jeu.getPlateau().getSizeplateau(); i++) {
            Text text = new Text(String.valueOf(i + 1));
            text.setStyle("-fx-font-size: 35;");
            int row = i / nombreColonnes;
            int col = i % nombreColonnes;

            gridPanel.add(text, col, row);
            gridPanel.setMargin(text, new Insets(30, 25, 50, 0));
            gridPanel.setAlignment(Pos.CENTER);
        }
}

    public void addPlayer(){
            gestionnaireJoueur.ajouterJoueur();
    }

    public void addGridPlayer(){
        int rowIndex = gestionnaireJoueur.getJoueurList().size();
        Joueur joueur = gestionnaireJoueur.getJoueurList().get(rowIndex - 1);

        Label idJoueurLabel = new Label("Joueur numéro " + joueur.getId());
        gridPlayer.add(idJoueurLabel, 0, rowIndex);

        Label caseJoueurLabel = new Label();
        caseJoueurLabel.setText("Case numéro: N/A");


        gridPlayer.add(caseJoueurLabel, 1, rowIndex);

    }

    public void changeGridPlayer(Joueur joueur){
        Label caseJoueurLabel = (Label) gridPlayer.getChildren().get(joueur.getId());
        if (joueur.getCurrentCase() != null) {
            caseJoueurLabel.textProperty().bind(Bindings.concat("Case numéro " + joueur.getCurrentCase().getNum()));
        } else {
            caseJoueurLabel.textProperty().bind(Bindings.concat("Case numéro: N/A"));
        }

    }

    public void start() {
        addPlay.setDisable(true);
        de.setDisable(false);
        btStart.setDisable(true);
        gestionnaireJoueur.InitaliseJoueur();
        currentJoueur = gestionnaireJoueur.getCurrentJoueur();
    }



    public void lanceDe() {
        idPlayer.textProperty().bind(currentJoueur.idProperty().asString());
        deSimple.lancer();
        idValeur.textProperty().bind(deSimple.valProperty().asString());
        if (deSimple.getVal() == 0){
            return;
        }
        System.out.println("Current Joueur = " + currentJoueur);
        jeu.CaseDeplacer(currentJoueur,deSimple.getVal() );
        currentJoueur = gestionnaireJoueur.switchCurrentPlayer();
        System.out.println();
    }
}
