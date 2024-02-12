package model.statement;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.PrgState;
import model.expression.Exp;
import model.type.StringType;
import model.type.Type;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFile implements IStmt{

    Exp exp;

    public OpenRFile(Exp e) {
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        Value v = exp.eval(state.getSymTable(), state.getHeap());
        if(v.getType().equals(new StringType())){
            StringValue sv = (StringValue) v;
            String filename = sv.getVal();
            MyIDictionary<String, BufferedReader> fileTable =state.getFileTable();
            if(!(fileTable.isDefined(filename))){
                BufferedReader br;
                try{
                    br = new BufferedReader(new FileReader(filename));
                } catch (FileNotFoundException e) {
                    throw new MyException(String.format("%s could not be opened", filename));
                }
                fileTable.add(filename, br);
            }
            else{
                throw new MyException(String.format("%s is already opened", filename));
            }
        }
        else{
            throw new MyException(String.format("%s does not evaluate to StringType", exp.toString()));
        }
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new OpenRFile(exp.deepCopy());
    }

    public String toString() {
        return String.format("OpenReadFile(%s)", exp.toString());
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws  MyException {
        if (exp.typecheck(typeEnv).equals(new StringType()))
            return typeEnv;
        else
            throw new MyException("OpenReadFile requires a string expression.");
    }
}
