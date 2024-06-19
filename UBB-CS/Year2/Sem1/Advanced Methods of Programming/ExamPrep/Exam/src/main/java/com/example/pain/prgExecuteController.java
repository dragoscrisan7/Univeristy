package com.example.pain;

import com.example.pain.controller.Controller;
import com.example.pain.exception.MyException;
import com.example.pain.model.adt.*;
import com.example.pain.model.statement.IStmt;
import com.example.pain.model.value.Value;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.input.MouseEvent;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.stream.Collectors;

class Pair<T1, T2> {
    T1 first;
    T2 second;

    public Pair(T1 first, T2 second) {
        this.first = first;
        this.second = second;
    }
}

public class prgExecuteController {
    private Controller cntrl;
    public void setController(Controller controller) {
        cntrl = controller;
        populate();
    }

    @FXML
    private TextField numberOfPrgStates;
    @FXML
    private TableView<Pair<Integer, Value>> heapTableView;
    @FXML
    private TableColumn<Pair<Integer, Value>, Integer> addressColumn;
    @FXML
    private TableColumn<Pair<Integer, Value>, String> valueColumn;
    @FXML
    private ListView<String> outputListView;
    @FXML
    private ListView<String> fileTableListView;
    @FXML
    private ListView<Integer> programStateIdentifiersListView;
    @FXML
    private TableView<Pair<String, Value>> symbolTableView;
    @FXML
    private TableColumn<Pair<String, Value>, String> variableNameColumn;
    @FXML
    private TableColumn<Pair<String, Value>, String> variableValueColumn;
    @FXML
    private ListView<String> executionStackListView;
    @FXML
    private Button runOneStepButton;
    @FXML
    private TableView<Map.Entry<Integer, javafx.util.Pair<Integer, List<Integer>>>> barrierTableView;

    @FXML
    private TableColumn<Map.Entry<Integer, javafx.util.Pair<Integer, List<Integer>>>, Integer> indexBarrierTableColumn;

    @FXML
    private TableColumn<Map.Entry<Integer, javafx.util.Pair<Integer, List<Integer>>>, Integer> valueBarrierTableColumn;

    @FXML
    private TableColumn<Map.Entry<Integer, javafx.util.Pair<Integer, List<Integer>>>, String> listBarrierTableColumn;


    @FXML
    public void initialize() {
        programStateIdentifiersListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        addressColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().first).asObject());
        valueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().second.toString()));
        variableNameColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().first));
        variableValueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().second.toString()));
        indexBarrierTableColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getKey()).asObject());
        valueBarrierTableColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getValue().getKey()).asObject());
        listBarrierTableColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue().getValue().toString()));
    }

    private PrgState getCurrentProgramState() {
        if (cntrl.getProgramStates().size() == 0)
            return null;
        else {
            int currentId = programStateIdentifiersListView.getSelectionModel().getSelectedIndex();
            if (currentId == -1)
                return cntrl.getProgramStates().get(0);
            else
                return cntrl.getProgramStates().get(currentId);
        }
    }

    private void populate() {
        populateHeapTableView();
        populateOutputListView();
        populateFileTableListView();
        populateProgramStateIdentifiersListView();
        populateSymbolTableView();
        populateExecutionStackListView();
        populateBarrierTableView();
    }

    @FXML
    private void changeProgramState(MouseEvent event) {
        populateExecutionStackListView();
        populateSymbolTableView();
    }


    private void populateNumberOfProgramStatesTextField() {
        List<PrgState> programStates = cntrl.getProgramStates();
        numberOfPrgStates.setText(String.valueOf(programStates.size()));
    }

    private void populateHeapTableView() {
        PrgState programState = getCurrentProgramState();
        MyIHeap<Integer, Value> heap = Objects.requireNonNull(programState).getHeap();
        ArrayList<Pair<Integer, Value>> heapEntries = new ArrayList<>();
        for(Map.Entry<Integer, Value> entry: heap.getContent().entrySet()) {
            heapEntries.add(new Pair<>(entry.getKey(), entry.getValue()));
        }
        heapTableView.setItems(FXCollections.observableArrayList(heapEntries));
    }
    private void populateSymbolTableView() {
        PrgState programState = getCurrentProgramState();
        MyIDictionary<String, Value> symbolTable = Objects.requireNonNull(programState).getSymTable();
        ArrayList<Pair<String, Value>> symbolTableEntries = new ArrayList<>();
        for (Map.Entry<String, Value> entry: symbolTable.getContent().entrySet()) {
            symbolTableEntries.add(new Pair<>(entry.getKey(), entry.getValue()));
        }
        symbolTableView.setItems(FXCollections.observableArrayList(symbolTableEntries));
    }

    private void populateOutputListView() {
        PrgState programState = getCurrentProgramState();
        List<String> output = new ArrayList<>();
        List<Value> outputList = Objects.requireNonNull(programState).getOut().getList();
        int index;
        for (index = 0; index < outputList.size(); index++){
            output.add(outputList.get(index).toString());
        }
        outputListView.setItems(FXCollections.observableArrayList(output));
    }

    private void populateFileTableListView() {
        PrgState programState = getCurrentProgramState();
        List<String> files = new ArrayList<>(Objects.requireNonNull(programState).getFileTable().getContent().keySet());
        fileTableListView.setItems(FXCollections.observableList(files));
    }

    private void populateExecutionStackListView() {
        PrgState programState = getCurrentProgramState();
        List<String> executionStackToString = new ArrayList<>();
        if (programState != null)
            for (IStmt statement: programState.getStk().getReversed()) {
                executionStackToString.add(statement.toString());
            }
        executionStackListView.setItems(FXCollections.observableList(executionStackToString));
    }

    private void populateProgramStateIdentifiersListView() {
        List<PrgState> programStates = cntrl.getProgramStates();
        List<Integer> idList = programStates.stream().map(PrgState::getId).collect(Collectors.toList());
        programStateIdentifiersListView.setItems(FXCollections.observableList(idList));
        populateNumberOfProgramStatesTextField();
    }
    private void populateBarrierTableView() {
        PrgState programState = getCurrentProgramState();
        MyIBarrierTable barrierTable = Objects.requireNonNull(programState).getBarrierTable();
        List<Map.Entry<Integer, javafx.util.Pair<Integer, List<Integer>>>> barrierList = new ArrayList<>();
        for (Map.Entry<Integer, javafx.util.Pair<Integer, List<Integer>>> entry: barrierTable.getBarrierTable().entrySet()) {
            barrierList.add(entry);
        }
        barrierTableView.setItems(FXCollections.observableArrayList(barrierList));
        barrierTableView.refresh();
    }

    @FXML
    private void runOneStep(MouseEvent mouseEvent) {
        if (cntrl != null) {
            try {
                List<PrgState> programStates = Objects.requireNonNull(cntrl.getProgramStates());
                if (programStates.size() > 0) {
                    cntrl.oneStep();
                    populate();
                    programStates = cntrl.removeCompletedPrg(cntrl.getProgramStates());
                    cntrl.setProgramStates(programStates);
                    populateProgramStateIdentifiersListView();
                } else {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("Error!");
                    alert.setHeaderText("An error has occured!");
                    alert.setContentText("There is nothing left to execute!");
                    alert.showAndWait();
                }
            } catch (MyException | InterruptedException e) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Execution error!");
                alert.setHeaderText("An execution error has occured!");
                alert.setContentText(e.getMessage());
                alert.showAndWait();
            }
        } else {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error!");
            alert.setHeaderText("An error has occured!");
            alert.setContentText("No program selected!");
            alert.showAndWait();
        }
    }
}
