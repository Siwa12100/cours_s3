package launch;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

import java.awt.*;

public class Launch extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        //Parent root = FXMLLoader.load(getClass().getResource())
        //Parent root = new BorderPane();
        //Parent root = new Button("coucouuu");

        Parent root = FXMLLoader.load(getClass().getResource("Index.fxml"));
        primaryStage.setTitle("Adiu a totes !");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }
}