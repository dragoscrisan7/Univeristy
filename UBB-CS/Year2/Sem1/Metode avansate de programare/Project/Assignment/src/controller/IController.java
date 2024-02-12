package controller;

import exception.MyException;
import model.adt.PrgState;

import java.io.IOException;
import java.util.List;

public interface IController {
    void oneStepForAllPrg(List<PrgState> programStates) throws MyException, InterruptedException;

    void allStep() throws MyException, IOException, InterruptedException;

    void setDisplayFlag(boolean value);
}
