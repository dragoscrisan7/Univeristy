package com.example.pain.model.expression;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.Value;

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