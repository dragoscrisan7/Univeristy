package com.example.pain.View;

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

import java.io.IOException;

class Interpreter {
    public static void main(String[] args) {
        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));

        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));

        try {
            ex1.typecheck(new MyDictionary<>());
            PrgState prg1 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyHeap(), ex1);
            IRepository repo1 = new Repository(prg1, "log1.txt");
            Controller ctr1 = new Controller(repo1);
            menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }




        menu.show();
    }
}