package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIStack;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.ValueExp;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.IntValue;

public class WaitStmt implements IStmt{
    private final int value;

    public WaitStmt(int value) {
        this.value = value;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        if (value != 0) {
            MyIStack<IStmt> exeStack = state.getStk();
            exeStack.push(new CompStmt(new PrintStmt(new ValueExp(new IntValue(value))),
                    new WaitStmt(value - 1)));
            state.setExeStack(exeStack);
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new WaitStmt(value);
    }

    @Override
    public String toString() {
        return String.format("wait(%s)", value);
    }
}
