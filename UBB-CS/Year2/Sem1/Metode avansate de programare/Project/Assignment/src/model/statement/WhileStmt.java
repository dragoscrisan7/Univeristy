package model.statement;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.PrgState;
import model.expression.Exp;
import model.type.BoolType;
import model.type.Type;
import model.value.BoolValue;
import model.value.Value;

public class WhileStmt implements IStmt{

    Exp e;
    IStmt stm;

    public WhileStmt(Exp e, IStmt stm){
        this.e = e;
        this.stm =stm;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        Value value = e.eval(state.getSymTable(), state.getHeap());
        MyIStack<IStmt> stack = state.getStk();
        if (!value.getType().equals(new BoolType()))
            throw new MyException(String.format("%s is not of BoolType", value));
        if (!(value instanceof BoolValue))
            throw new MyException(String.format("%s is not a BoolValue", value));
        BoolValue boolValue = (BoolValue) value;
        if (boolValue.getVal()) {
            stack.push(this.deepCopy());
            stack.push(stm);
        }
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new WhileStmt(e.deepCopy(), stm.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("while(%s){%s}", e, stm);
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typeExpr = e.typecheck(typeEnv);
        if (typeExpr.equals(new BoolType())) {
            stm.typecheck(typeEnv.deepCopy());
            return typeEnv;
        } else
            throw new MyException("The condition of WHILE does not have the type Bool.");
    }
}
