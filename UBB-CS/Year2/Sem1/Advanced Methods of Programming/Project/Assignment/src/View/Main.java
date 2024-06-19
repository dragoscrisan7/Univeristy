package View;

import controller.Controller;
import controller.IController;
import exception.MyException;
import model.adt.*;
import model.expression.ArithExp;
import model.expression.VarExp;
import model.statement.*;
import model.type.BoolType;
import model.type.IntType;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.Value;
import repository.IRepository;
import repository.Repository;
import model.expression.ValueExp;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Objects;
import java.util.Scanner;
/*
public class Main {

    public static void main(String args[]) throws MyException, IOException {

        while(true){

            System.out.println("What program would you like to run?");
            System.out.println("1. input a number; Print(number)");
            System.out.println("2. input a number;int b; int a;a=number-7*2;b=a+number;Print(b)");
            System.out.println("3. input bool a; int v;If a is true v=1, else v=0;Print(v)");

            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            System.out.print("Enter option: ");
            String s = br.readLine();
            Scanner scan = new Scanner(System.in);
            boolean flag;
            if(!s.equals("exit")){
                System.out.println("1. With execution steps");
                System.out.println("2. Without execution steps");
                System.out.print("Enter option: ");
                String f = br.readLine();

                if(f.equals("1")){
                    flag = true;
                }else{
                    flag = false;
                }
            }
            else {
                flag = false;
            }




            if(s.equals("1")){
                System.out.print("variable = ");
                int num = scan.nextInt();
                IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(num))), new PrintStmt(new
                                VarExp("v"))));

                MyIStack stk = new MyStack();
                MyIDictionary<String, Value> symtbl = new MyDictionary<>();
                MyIList<Value> ot = new MyList<>();
                PrgState program = new PrgState(stk, symtbl, ot, ex1);

                IRepository repo = new Repository(program);
                IController ctrl = new Controller(repo);

                ctrl.allStep(flag);

            }else if(s.equals("2")){
                System.out.print("variable = ");
                int num = scan.nextInt();
                IStmt ex2 = new CompStmt( new VarDeclStmt("a", new IntType()),
                        new CompStmt( new VarDeclStmt("b", new IntType()),
                                new CompStmt(new AssignStmt("a", new ArithExp('-', new ValueExp(new IntValue(num)),
                                        new ArithExp('*', new ValueExp(new IntValue(7)), new ValueExp(new IntValue(2))))),
                                        new CompStmt(new AssignStmt("b", new ArithExp('+', new VarExp("a"), new ValueExp(new
                                                IntValue(num)))), new PrintStmt(new VarExp("b"))))));

                MyIStack stk = new MyStack();
                MyIDictionary<String, Value> symtbl = new MyDictionary<>();
                MyIList<Value> ot = new MyList<>();
                PrgState program = new PrgState(stk, symtbl, ot, ex2);

                IRepository repo = new Repository(program);
                IController ctrl = new Controller(repo);

                ctrl.allStep(flag);

            }else if(s.equals("3")){
                System.out.print("x = ");
                String x = br.readLine();
                boolean a;
                if(Objects.equals(x, "true"))
                    a = true;
                else
                    a = false;
                IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                        new CompStmt(new VarDeclStmt("v", new IntType()),
                                new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(a))),
                                        new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new
                                                IntValue(1))), new AssignStmt("v", new ValueExp(new IntValue(0)))),
                                                new PrintStmt(new VarExp("v"))))));

                MyIStack stk = new MyStack();
                MyIDictionary<String, Value> symtbl = new MyDictionary<>();
                MyIList<Value> ot = new MyList<>();
                PrgState program = new PrgState(stk, symtbl, ot, ex3);

                IRepository repo = new Repository(program);
                IController ctrl = new Controller(repo);

                ctrl.allStep(flag);

            }
            else if(s.equals("exit")){
                return;
            }
            else{
                System.out.println("I didn't recognise the command\n");
            }
        }
    }
}
*/
