package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIStack;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.type.BoolType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.BoolValue;
import com.example.pain.model.value.Value;

public class repeatUntillStmt implements IStmt{
    IStmt stm;
    Exp exp;

    public repeatUntillStmt(IStmt stm, Exp exp) {
        this.stm = stm;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        Value value = exp.eval(state.getSymTable(), state.getHeap());
        MyIStack<IStmt> stack = state.getStk();
        if (!value.getType().equals(new BoolType()))
            throw new MyException(String.format("%s is not of BoolType", value));
        if (!(value instanceof BoolValue))
            throw new MyException(String.format("%s is not a BoolValue", value));
        BoolValue boolValue = (BoolValue) value;
        if(!boolValue.getVal()){
            stack.push(this.deepCopy());
            stack.push(stm);
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typeExp = exp.typecheck(typeEnv);
        if(typeExp.equals(new BoolType())){
            stm.typecheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else{
            throw new MyException("The condition of Repeat...Untill should be of type bool.");
        }
    }

    @Override
    public IStmt deepCopy() {
        return new repeatUntillStmt(stm.deepCopy(), exp.deepCopy());
    }
    @Override
    public String toString() {
        return String.format("repeat{%s}untill(%s)", stm, exp);
    }
}
