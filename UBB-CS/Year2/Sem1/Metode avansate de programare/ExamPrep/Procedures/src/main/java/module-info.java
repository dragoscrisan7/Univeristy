module com.example.pain {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.pain to javafx.fxml;
    exports com.example.pain;

    //opens com.example.pain.MainGui to javafx.fxml;

    opens com.example.pain.controller to javafx.fxml;
    exports com.example.pain.controller;

    opens com.example.pain.repository to javafx.fxml;
    exports com.example.pain.repository;


}