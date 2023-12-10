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

        //ConsoleGame.main(null);

        FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/Index.fxml"));
        Parent root = loader.load();

        Scene scene = new Scene(root);
        primaryStage.setScene(scene);

        primaryStage.setTitle("Adiu a totes ! ");
        primaryStage.show();
    }
}
