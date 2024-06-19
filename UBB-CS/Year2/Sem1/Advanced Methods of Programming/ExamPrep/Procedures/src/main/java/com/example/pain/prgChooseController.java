package com.example.pain;

import com.example.pain.controller.Controller;
import com.example.pain.exception.MyException;
import com.example.pain.model.adt.*;
import com.example.pain.model.expression.*;
import com.example.pain.model.statement.*;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.RefType;
import com.example.pain.model.type.StringType;
import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.StringValue;
import com.example.pain.model.value.Value;
import com.example.pain.repository.IRepository;
import com.example.pain.repository.Repository;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class prgChooseController {
    private MyIProcTable procTable;

    private prgExecuteController prgEC;

    public void setProgramExecutorController(prgExecuteController prgEC) {
        this.prgEC = prgEC;
    }
    @FXML
    private ListView<IStmt> programsLV;

    @FXML
    private Button Scene1Button;

    @FXML
    private ObservableList<IStmt> getAllStatements() {
        List<IStmt> allStatements = new ArrayList<>();

        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));
        allStatements.add(ex1);


        IStmt sumProc = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                        new AssignStmt("v", new ArithExp('+', new VarExp("a"), new VarExp("b"))),
                        new PrintStmt(new VarExp("v"))
                )
        );

        List<String> varSum = new ArrayList<>();
        varSum.add("a");
        varSum.add("b");
        procTable.put("sum", new Pair<>(varSum, sumProc));

        IStmt prodProc = new CompStmt(
                new VarDeclStmt("v" , new IntType()),
                new CompStmt(
                        new AssignStmt("v", new ArithExp('*', new VarExp("a"), new VarExp("b"))),
                        new PrintStmt(new VarExp("v"))
                )
        );

        List<String> varProd = new ArrayList<>();
        varProd.add("a");
        varProd.add("b");
        procTable.put("product", new Pair<>(varProd, prodProc));

        IStmt ex2 = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                        new VarDeclStmt("w", new IntType()),
                        new CompStmt(
                                new AssignStmt("v", new ValueExp(new IntValue(2))),
                                new CompStmt(
                                        new AssignStmt("w", new ValueExp(new IntValue(5))),
                                        new CompStmt(
                                                new CallProcStmt("sum", new ArrayList<>(Arrays.asList(new ArithExp('*', new VarExp("v"), new ValueExp(new IntValue(10))), new VarExp("w")))),
                                                new CompStmt(
                                                        new PrintStmt(new VarExp("v")),
                                                        new ForkStmt(
                                                                new CompStmt(
                                                                        new CallProcStmt("product", new ArrayList<>(Arrays.asList(new VarExp("v"), new VarExp("w")))),
                                                                        new ForkStmt(
                                                                                new CallProcStmt("sum", new ArrayList<>(Arrays.asList(new VarExp("v"), new VarExp("w"))))
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
        allStatements.add(ex2);
        return FXCollections.observableArrayList(allStatements);
    }

    @FXML
    public void initialize() {
        this.procTable = new MyProcTable();
        programsLV.setItems(getAllStatements());
        programsLV.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }


    @FXML
    private void displayProgram(ActionEvent actionEvent) {
        IStmt selectedStatement = programsLV.getSelectionModel().getSelectedItem();
        if (selectedStatement == null) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error encountered!");
            alert.setContentText("No statement selected!");
            alert.showAndWait();
        } else {
            int id = programsLV.getSelectionModel().getSelectedIndex();
            try {
                selectedStatement.typecheck(new MyDictionary<>());
                MyIStack<MyIDictionary<String, Value>> symTableStack = new MyStack<>();
                symTableStack.push(new MyDictionary<>());
                PrgState prgs = new PrgState(new MyStack<>(), symTableStack, new MyList<>(), new MyDictionary<>(), procTable, new MyHeap(), selectedStatement);
                IRepository repository = new Repository(prgs, "log" + (id + 1) + ".txt");
                Controller controller = new Controller(repository);
                prgEC.setController(controller);
            } catch (MyException | IOException exception) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error encountered!");
                alert.setContentText(exception.getMessage());
                alert.showAndWait();
            }
        }
    }

}