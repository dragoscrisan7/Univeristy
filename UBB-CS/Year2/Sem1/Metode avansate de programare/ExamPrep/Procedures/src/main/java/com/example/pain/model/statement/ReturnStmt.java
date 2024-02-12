package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.type.Type;

public class ReturnStmt implements IStmt{
    @Override
    public PrgState execute(PrgState state) throws MyException {
        state.getSymTable().pop();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new ReturnStmt();
    }

    @Override
    public String toString() {
        return "return";
    }
}
