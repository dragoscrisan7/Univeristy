package com.example.pain.View;

import com.example.pain.controller.Controller;
import com.example.pain.exception.MyException;

import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;

public class RunExample extends Command {
    private Controller ctr;

    public RunExample(String key, String desc,Controller ctr){
        super(key, desc);
        this.ctr=ctr;
    }
    @Override
    public void execute() {
        try{
            System.out.println("Do you want to display the steps?[Y/n]");
            Scanner readOption = new Scanner(System.in);
            String option = readOption.next();
            ctr.setDisplayFlag(Objects.equals(option, "Y"));
            ctr.allStep();}
        catch (MyException | IOException | InterruptedException exception) {
            System.out.println("\u001B[31m" + exception.getMessage() + "\u001B[0m");
        }
    }
}