package com.example.pain.model.expression;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.BoolValue;
import com.example.pain.model.value.Value;

public class NotExp implements Exp{
    private final Exp expression;

    public NotExp(Exp expression) {
        this.expression = expression;
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return expression.typecheck(typeEnv);
    }

    @Override
    public Value eval(MyIDictionary<String, Value> table, MyIHeap<Integer, Value> heap) throws MyException {
        BoolValue value = (BoolValue) expression.eval(table, heap);
        if (!value.getVal())
            return new BoolValue(true);
        else
            return new BoolValue(false);
    }

    @Override
    public Exp deepCopy() {
        return new NotExp(expression.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("!(%s)", expression);
    }
}
