package MainGui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.IOException;

public class main extends Application {



    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader programListLoader = new FXMLLoader();
        programListLoader.setLocation(main.class.getResource("Sample.fxml"));
        Parent programListRoot = programListLoader.load();
        Scene programListScene = new Scene(programListRoot, 600, 550);
        ProgramChooserController programChooserController = programListLoader.getController();
        stage.setTitle("Select a program");
        stage.setScene(programListScene);
        stage.show();






    }
}
