package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIStack;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.expression.NotExp;
import com.example.pain.model.type.BoolType;
import com.example.pain.model.type.Type;

public class RepeatUntillStmt implements IStmt{
    private final IStmt statement;
    private final Exp expression;

    public RepeatUntillStmt(IStmt statement, Exp expression) {
        this.statement = statement;
        this.expression = expression;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> exeStack = state.getStk();
        IStmt converted = new CompStmt(statement, new WhileStmt(new NotExp(expression), statement));
        exeStack.push(converted);
        state.setExeStack(exeStack);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type type = expression.typecheck(typeEnv);
        if (type.equals(new BoolType())) {
            statement.typecheck(typeEnv.deepCopy());
            return typeEnv;
        } else {
            throw new MyException("Expression in the repeat statement must be of Bool type!");
        }
    }

    @Override
    public IStmt deepCopy() {
        return new RepeatUntillStmt(statement.deepCopy(), expression.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("repeat(%s) until (%s)", statement, expression);
    }

}
