package com.example.pain.model.expression;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.Value;

public class VarExp implements Exp{
    String id;

    public VarExp(String v) {
        this.id = v;
    }
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer,Value> heap) throws MyException
    {
        if(!tbl.isDefined(id))
            throw new MyException("Variable not defined in symbol table");
        return tbl.lookup(id);
    }
    public String getId() {
        return id;
    }
    public void setId(String id) {
        this.id = id;
    }
    public String toString() {
        return id;
    }
    public Exp deepCopy() {
        return new VarExp(id);
    }
    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        return typeEnv.lookup(id);
    }
}