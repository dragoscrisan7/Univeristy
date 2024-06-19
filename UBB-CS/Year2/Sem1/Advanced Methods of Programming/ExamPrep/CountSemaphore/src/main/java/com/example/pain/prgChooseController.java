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
import com.example.pain.repository.IRepository;
import com.example.pain.repository.Repository;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class prgChooseController {

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

        IStmt ex2 = new CompStmt(new VarDeclStmt("x", new IntType()),
                new CompStmt(new VarDeclStmt("y", new IntType()),
                        new CompStmt(new AssignStmt("x", new ArithExp('*', new ValueExp(new IntValue(7)), new
                                ArithExp('*', new ValueExp(new IntValue(3)), new ValueExp(new IntValue(2))))),
                                new CompStmt(new AssignStmt("y", new ArithExp('+', new VarExp("x"), new ValueExp(new
                                        IntValue(7)))), new PrintStmt(new VarExp("y"))))));
        allStatements.add(ex2);

        IStmt ex3 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(new OpenRFile(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                                        new CloseReadFile(new VarExp("varf"))))))))));
        allStatements.add(ex3);

        IStmt ex4 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())), new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                        new CompStmt(new NewStmt("a", new VarExp("v")),
                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new VarExp("a")))))));
        allStatements.add(ex4);

        IStmt ex5 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(5))),
                                new CompStmt(new AssignStmt("b", new ValueExp(new IntValue(7))),
                                        new IfStmt(new RelExp(">", new VarExp("a"),
                                                new VarExp("b")),new PrintStmt(new VarExp("a")),
                                                new PrintStmt(new VarExp("b")))))));
        allStatements.add(ex5);

        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())), new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                new CompStmt(new PrintStmt(new rH(new VarExp("v"))), new CompStmt(new wH("v", new ValueExp(new IntValue(30))), new PrintStmt(new ArithExp('+', new rH(new VarExp("v")), new ValueExp(new IntValue(5))))))));
        allStatements.add(ex6);

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new rH(new rH(new VarExp("a")))))))));
        allStatements.add(ex7);

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelExp(">", new VarExp("v"), new ValueExp(new IntValue(0))),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v",new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));
        allStatements.add(ex8);

        IStmt ex9 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new wH("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new rH(new VarExp("a"))))))),
                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new rH(new VarExp("a")))))))));
        allStatements.add(ex9);

        IStmt ex10 = new CompStmt(
                new VarDeclStmt("a", new IntType()),
                new CompStmt(
                    new VarDeclStmt("b", new IntType()),
                    new CompStmt(
                        new VarDeclStmt("c", new IntType()),
                        new CompStmt(
                            new AssignStmt("a", new ValueExp(new IntValue(1))),
                            new CompStmt(
                                new AssignStmt("b", new ValueExp(new IntValue(2))),
                                new CompStmt(
                                    new AssignStmt("c", new ValueExp(new IntValue(5))),
                                    new CompStmt(
                                        new SwitchStmt(
                                                new ArithExp('*', new VarExp("a"), new ValueExp(new IntValue(10))),
                                                new ArithExp('*', new VarExp("b"), new VarExp("c")),
                                                new ValueExp(new IntValue(10)),
                                                new CompStmt(
                                                    new PrintStmt(new VarExp("a")),
                                                    new PrintStmt(new VarExp("b"))
                                                ),
                                                new CompStmt(
                                                    new PrintStmt(new ValueExp(new IntValue(100))),
                                                    new PrintStmt(new ValueExp(new IntValue(200)))
                                                ),
                                                new PrintStmt(new ValueExp(new IntValue(300)))
                                        ),
                                        new PrintStmt(new ValueExp(new IntValue(300)))
                                    )
                                )
                            )
                        )
                    )
                )
        );
        allStatements.add(ex10);

        IStmt ex11 = new CompStmt(
                new VarDeclStmt("v1", new RefType(new IntType())),
                new CompStmt(
                        new VarDeclStmt("cnt", new IntType()),
                        new CompStmt(
                                new NewStmt("v1", new ValueExp(new IntValue(1))),
                                new CompStmt(
                                        new createSemaphoreStmt("cnt", new rH(new VarExp("v1"))),
                                        new CompStmt(
                                                new ForkStmt(
                                                        new CompStmt(
                                                                new AcquireStmt("cnt"),
                                                                new CompStmt(
                                                                        new wH("v1", new ArithExp('*', new rH(new VarExp("v1")), new ValueExp(new IntValue(10)))),
                                                                        new CompStmt(
                                                                                new PrintStmt(new rH(new VarExp("v1"))),
                                                                                new releaseStmt("cnt")
                                                                        )
                                                                )
                                                        )
                                                ),
                                                new CompStmt(
                                                        new ForkStmt(
                                                                new CompStmt(
                                                                        new AcquireStmt("cnt"),
                                                                        new CompStmt(
                                                                                new wH("v1", new ArithExp('*',  new rH(new VarExp("v1")), new ValueExp(new IntValue(10)))),
                                                                                new CompStmt(
                                                                                        new wH("v1", new ArithExp('*',  new rH(new VarExp("v1")), new ValueExp(new IntValue(2)))),
                                                                                        new CompStmt(
                                                                                                new PrintStmt(new rH(new VarExp("v1"))),
                                                                                                new releaseStmt("cnt")
                                                                                        )
                                                                                )
                                                                        )
                                                                )
                                                        ),
                                                        new CompStmt(
                                                                new AcquireStmt("cnt"),
                                                                new CompStmt(
                                                                        new PrintStmt(new ArithExp('-', new rH(new VarExp("v1")), new ValueExp(new IntValue(1)))),
                                                                        new releaseStmt("cnt")
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
        allStatements.add(ex11);
        return FXCollections.observableArrayList(allStatements);
    }

    @FXML
    public void initialize() {
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
                PrgState prgs = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MySemaphore(), new MyHeap(), selectedStatement);
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