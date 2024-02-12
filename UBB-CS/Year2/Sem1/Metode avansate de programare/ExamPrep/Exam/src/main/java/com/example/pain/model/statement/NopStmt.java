package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.type.Type;

public class NopStmt implements IStmt {
     public PrgState execute(PrgState state) throws MyException{
         return null;
     }
    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }

     public String toString(){return super.toString();}
     public IStmt deepCopy() {
        return new NopStmt();
    }
}