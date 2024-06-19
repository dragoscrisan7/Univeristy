package com.example.pain.model.expression;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.Value;

public class MulExp implements Exp{
    private final Exp expression1;
    private final Exp expression2;

    public MulExp(Exp expression1, Exp expression2) {
        this.expression1 = expression1;
        this.expression2 = expression2;
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type type1 = expression1.typecheck(typeEnv);
        Type type2 = expression2.typecheck(typeEnv);
        if (type1.equals(new IntType()) && type2.equals(new IntType()))
            return new IntType();
        else
            throw new MyException("Expressions in the MUL should be int!");
    }

    @Override
    public Value eval(MyIDictionary<String, Value> table, MyIHeap<Integer, Value> heap) throws MyException {
        Exp converted = new ArithExp('-',
                new ArithExp('*', expression1, expression2),
                new ArithExp('+', expression1, expression2));
        return converted.eval(table, heap);
    }

    @Override
    public Exp deepCopy() {
        return new MulExp(expression1.deepCopy(), expression2.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("MUL(%s, %s)", expression1, expression2);
    }
}
