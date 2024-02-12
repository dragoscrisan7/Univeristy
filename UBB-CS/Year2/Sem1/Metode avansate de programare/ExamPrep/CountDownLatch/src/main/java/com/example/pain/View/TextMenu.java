package com.example.pain.View;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyDictionary;
import com.example.pain.model.adt.MyIDictionary;

import java.util.Scanner;


public class TextMenu {
    private MyIDictionary<String, Command> commands;

    public TextMenu() {
        commands = new MyDictionary<>();
    }

    public void addCommand(Command c) {
        commands.add(c.getKey(), c);
    }

    private void printMenu() {
        for (Command com : commands.values()) {
            String line = String.format("%4s : %s", com.getKey(), com.getDescription());
            System.out.println(line);
        }
    }

    public void show() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            printMenu();
            System.out.printf("Input the option: ");
            String key = scanner.nextLine();

            try{
                Command com = commands.lookup(key);
                com.execute();
            } catch (MyException e) {
                System.out.println("Invalid option");
            }
        }
    }
}
