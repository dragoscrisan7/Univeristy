package model.statement;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIList;
import model.adt.PrgState;
import model.expression.Exp;
import model.type.Type;
import model.value.Value;

public class PrintStmt implements IStmt {
    Exp exp;

    public PrintStmt(Exp v) {
        this.exp = v;
    }

    public String toString(){ return "print(" + exp.toString()+")";}

    public IStmt deepCopy() {
        return new PrintStmt(exp.deepCopy());
    }

    public PrgState execute(PrgState state) throws MyException {
        MyIList<Value> out = state.getOut();
        out.add(exp.eval(state.getSymTable(), state.getHeap()));
        System.out.println(exp.eval(state.getSymTable(), state.getHeap()));
        return null;
    }
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String,Type> typeEnv) throws
            MyException{
        exp.typecheck(typeEnv);
        return typeEnv;
    }
}

