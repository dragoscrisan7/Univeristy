package repository;

import exception.MyException;
import model.adt.PrgState;

import java.io.IOException;
import java.util.List;

public interface IRepository {

    List<PrgState> getPrgList();
    void setPrgList(List<PrgState> prgStates);

    void addProgram(PrgState prgS);
    void emptyLogFile() throws IOException;

    void logPrgStateExec(PrgState prgS) throws MyException, IOException;
}
