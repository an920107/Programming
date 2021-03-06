/**
 * Assignment 11
 * Student Number: 110502557
 * Course: 2022-CE1004-A
 */

package A11_110502557.application;

import A11_110502557.application.Constants.FXMLFiles;
import A11_110502557.application.Controllers.SceneController;
import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception {
        stage.setTitle("Greedy Snake");
        stage.setResizable(false);

        try (SceneController sc = new SceneController(FXMLFiles.TITLE_SCREEN)) {
            sc.show(stage);
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }
}