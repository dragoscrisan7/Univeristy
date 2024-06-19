package model.expression;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.type.Type;
import model.value.Value;

public class ValueExp implements Exp{
    Value e;
    public ValueExp(Value val) {
        this.e = val;
    }
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer,Value> heap) throws MyException {
        return e;
    }
    public String toString() {
        return "" + e;
    }
    public Exp deepCopy() {
        return new ValueExp(e.deepCopy());
    }
    @Override
    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        return e.getType();
    }
}