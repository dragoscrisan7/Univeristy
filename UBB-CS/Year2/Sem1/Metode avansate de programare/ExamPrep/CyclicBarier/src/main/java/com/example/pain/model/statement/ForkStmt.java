package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.*;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.Value;

import java.util.Map;

public class ForkStmt implements IStmt{
    private final IStmt stm;


    public ForkStmt(IStmt statement) {
        this.stm = statement;
    }

    @Override
    public IStmt deepCopy() {
        return new ForkStmt(stm.deepCopy());
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> newStack = new MyStack<>();
        newStack.push(stm);
        MyIDictionary<String, Value> newSymTable = new MyDictionary<>();
        for (Map.Entry<String, Value> entry: state.getSymTable().getContent().entrySet()) {
            newSymTable.put(entry.getKey(), entry.getValue().deepCopy());
        }

        return new PrgState(newStack, newSymTable, state.getOut(), state.getFileTable(), state.getBarrierTable(), state.getHeap());
    }

    @Override
    public String toString() {
        return String.format("Fork(%s)", stm.toString());
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        stm.typecheck(typeEnv.deepCopy());
        return typeEnv;
    }
}
