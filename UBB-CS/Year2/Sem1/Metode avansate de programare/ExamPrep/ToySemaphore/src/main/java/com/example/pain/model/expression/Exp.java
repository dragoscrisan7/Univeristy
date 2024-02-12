package com.example.pain.model.expression;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.Value;

public interface Exp {
    public Value eval(MyIDictionary<String,Value> tbl, MyIHeap<Integer,Value> hp) throws MyException;

    Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException;

    Exp deepCopy();
}
