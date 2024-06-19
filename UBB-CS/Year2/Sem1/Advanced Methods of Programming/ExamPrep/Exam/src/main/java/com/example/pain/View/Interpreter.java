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
            PrgState prg1 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyBarrierTable(), new MyHeap(), ex1);
            IRepository repo1 = new Repository(prg1, "log1.txt");
            Controller ctr1 = new Controller(repo1);
            menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }

        IStmt ex2 = new CompStmt(new VarDeclStmt("x", new IntType()),
                new CompStmt(new VarDeclStmt("y", new IntType()),
                        new CompStmt(new AssignStmt("x", new ArithExp('*', new ValueExp(new IntValue(7)), new
                                ArithExp('*', new ValueExp(new IntValue(3)), new ValueExp(new IntValue(2))))),
                                new CompStmt(new AssignStmt("y", new ArithExp('+', new VarExp("x"), new ValueExp(new
                                        IntValue(7)))), new PrintStmt(new VarExp("y"))))));
        try {
            ex2.typecheck(new MyDictionary<>());
            PrgState prg2 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyBarrierTable(), new MyHeap(), ex2);
            IRepository repo2 = new Repository(prg2, "log2.txt");
            Controller ctr2 = new Controller(repo2);
            menu.addCommand(new RunExample("2", ex2.toString(), ctr2));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }

        IStmt ex3 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(new OpenRFile(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                                        new CloseReadFile(new VarExp("varf"))))))))));



        try {
            ex3.typecheck(new MyDictionary<>());
            PrgState prg3 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyBarrierTable(), new MyHeap(), ex3);
            IRepository repo3 = new Repository(prg3, "log3.txt");
            Controller ctr3 = new Controller(repo3);
            menu.addCommand(new RunExample("3", ex3.toString(), ctr3));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }


        IStmt ex5 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(5))),
                                new CompStmt(new AssignStmt("b", new ValueExp(new IntValue(7))),
                                        new IfStmt(new RelExp(">", new VarExp("a"),
                                                new VarExp("b")),new PrintStmt(new VarExp("a")),
                                                new PrintStmt(new VarExp("b")))))));

        try {
            ex5.typecheck(new MyDictionary<>());
            PrgState prg5 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyBarrierTable(), new MyHeap(), ex5);
            IRepository repo5 = new Repository(prg5, "log5.txt");
            Controller ctr5 = new Controller(repo5);
            menu.addCommand(new RunExample("5", ex5.toString(), ctr5));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }

        IStmt ex4 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())), new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                        new CompStmt(new NewStmt("a", new VarExp("v")),
                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new VarExp("a")))))));
        try {
            ex4.typecheck(new MyDictionary<>());
            PrgState prg4 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyBarrierTable(), new MyHeap(), ex4);
            IRepository repo4 = new Repository(prg4, "log4.txt");
            Controller ctr4 = new Controller(repo4);
            menu.addCommand(new RunExample("4", ex4.toString(), ctr4));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }



        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())), new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                new CompStmt(new PrintStmt(new rH(new VarExp("v"))), new CompStmt(new wH("v", new ValueExp(new IntValue(30))), new PrintStmt(new ArithExp('+', new rH(new VarExp("v")), new ValueExp(new IntValue(5))))))));
        try {
            ex6.typecheck(new MyDictionary<>());
            PrgState prg6 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyBarrierTable(), new MyHeap(), ex6);
            IRepository repo6 = new Repository(prg6, "log6.txt");
            Controller ctr6 = new Controller(repo6);
            menu.addCommand(new RunExample("6", ex6.toString(), ctr6));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new rH(new rH(new VarExp("a")))))))));
        try {
            ex7.typecheck(new MyDictionary<>());
            PrgState prg7 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyBarrierTable(), new MyHeap(), ex7);
            IRepository repo7 = new Repository(prg7, "log7.txt");
            Controller ctr7 = new Controller(repo7);
            menu.addCommand(new RunExample("7", ex7.toString(), ctr7));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelExp(">", new VarExp("v"), new ValueExp(new IntValue(0))),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v",new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));
        try {
            ex8.typecheck(new MyDictionary<>());
            PrgState prg8 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyBarrierTable(), new MyHeap(), ex8);
            IRepository repo8 = new Repository(prg8, "log8.txt");
            Controller ctr8 = new Controller(repo8);
            menu.addCommand(new RunExample("8", ex8.toString(), ctr8));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }

        IStmt ex9 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new wH("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new rH(new VarExp("a"))))))),
                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new rH(new VarExp("a")))))))));

        try {
            ex9.typecheck(new MyDictionary<>());
            PrgState prg9 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new MyBarrierTable(), new MyHeap(), ex9);
            IRepository repo9 = new Repository(prg9, "log9.txt");
            Controller ctr9 = new Controller(repo9);
            menu.addCommand(new RunExample("9", ex9.toString(), ctr9));
        } catch (IOException | MyException e) {
            System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
        }


        menu.show();
    }
}