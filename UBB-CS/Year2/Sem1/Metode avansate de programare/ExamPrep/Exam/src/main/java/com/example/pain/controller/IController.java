package com.example.pain.controller;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.PrgState;

import java.io.IOException;
import java.util.List;

public interface IController {
    void oneStepForAllPrg(List<PrgState> programStates) throws MyException, InterruptedException;

    void allStep() throws MyException, IOException, InterruptedException;

    void oneStep() throws MyException, InterruptedException;

    void setDisplayFlag(boolean value);

    List<PrgState> getProgramStates();

    void setProgramStates(List<PrgState> programStates);
}
