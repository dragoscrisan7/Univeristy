package model.statement;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.PrgState;
import model.expression.Exp;
import model.type.StringType;
import model.type.Type;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseReadFile implements IStmt{

    Exp exp;

    public CloseReadFile(Exp e){exp = e;}

    @Override
    public PrgState execute(PrgState state) throws MyException {
        Value value = exp.eval(state.getSymTable(), state.getHeap());
        if (!value.getType().equals(new StringType()))
            throw new MyException(String.format("%s does not evaluate to StringValue", exp));
        StringValue fileName = (StringValue) value;
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();
        if (!fileTable.isDefined(fileName.getVal()))
            throw new MyException(String.format("%s is not present in the FileTable", value));
        BufferedReader br = fileTable.lookup(fileName.getVal());
        try {
            br.close();
        } catch (IOException e) {
            throw new MyException(String.format("Unexpected error in closing %s", value));
        }
        fileTable.remove(fileName.getVal());
        state.setFileTable(fileTable);
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new CloseReadFile(exp.deepCopy());
    }
    public String toString() {
        return String.format("CloseReadFile(%s)", exp.toString());
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException{
        if (exp.typecheck(typeEnv).equals(new StringType()))
            return typeEnv;
        else
            throw new MyException("CloseReadFile requires a string expression.");
    }
}
