package model.expression;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.type.Type;
import model.value.Value;

public interface Exp {
    public Value eval(MyIDictionary<String,Value> tbl, MyIHeap<Integer,Value> hp) throws MyException;

    Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException;

    Exp deepCopy();
}
