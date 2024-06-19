package model.statement;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.PrgState;
import model.type.Type;

public class CompStmt implements IStmt {
    IStmt first;
    IStmt snd;

    public CompStmt(IStmt s1, IStmt s2) {
        first = s1;
        snd = s2;
    }

    public String toString() {
        return "(" + first.toString() + "|" + snd.toString() + ")";
    }

    public IStmt deepCopy() {
        return new CompStmt(first.deepCopy(), snd.deepCopy());
    }
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getStk();
        stk.push(snd);
        stk.push(first);
        return null;
    }

    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws
            MyException{
        return snd.typecheck(first.typecheck(typeEnv));
    }
}
