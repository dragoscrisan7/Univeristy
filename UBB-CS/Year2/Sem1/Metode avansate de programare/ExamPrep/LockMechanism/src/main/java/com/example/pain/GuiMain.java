package com.example.pain;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class GuiMain extends Application {

    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader programListLoader = new FXMLLoader(GuiMain.class.getResource("hello-view.fxml"));
        Scene programListScene = new Scene(programListLoader.load(), 600, 550);
        prgChooseController prgCC = programListLoader.getController();
        stage.setTitle("Select a program");
        stage.setScene(programListScene);
        stage.show();

        FXMLLoader executeProgram = new FXMLLoader(GuiMain.class.getResource("execute-view.fxml"));
        Scene executeScene = new Scene(executeProgram.load(), 600, 600);
        prgExecuteController prgEC = executeProgram.getController();
        prgCC.setProgramExecutorController(prgEC);
        Stage newStage = new Stage();
        newStage.setTitle("Program info");
        newStage.setScene(executeScene);
        newStage.show();
    }
    public static void main(String[] args) {
        launch();
    }
}