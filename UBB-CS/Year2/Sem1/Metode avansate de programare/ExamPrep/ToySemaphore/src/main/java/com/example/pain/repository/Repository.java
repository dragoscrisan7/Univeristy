package com.example.pain.repository;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    private List<PrgState> programStates;
    private final String logFilePath;
    public Repository(PrgState state, String logFilePath) throws IOException {
        this.programStates = new ArrayList<>();
        this.logFilePath = logFilePath;
        this.addProgram(state);
        this.emptyLogFile();
    }

    @Override
    public List<PrgState> getPrgList() {
        return this.programStates;
    }
    @Override
    public void setPrgList(List<PrgState> programStates) {
        this.programStates = programStates;
    }
    @Override
    public void addProgram(PrgState program) {
        this.programStates.add(program);
    }


    @Override
    public void logPrgStateExec(PrgState prgS) throws MyException, IOException {
        PrintWriter logFile;
        logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
        logFile.println(prgS.programStateToString());
        logFile.close();
    }

    public void emptyLogFile() throws IOException {
        PrintWriter logFile;
        logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, false)));
        logFile.close();
    }
}
