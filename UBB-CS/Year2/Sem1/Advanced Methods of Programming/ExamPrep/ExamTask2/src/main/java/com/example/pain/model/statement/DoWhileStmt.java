package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.type.BoolType;
import com.example.pain.model.type.Type;

public class DoWhileStmt implements IStmt{
    private final IStmt statement;
    private final Exp expression;

    public DoWhileStmt(Exp expression, IStmt statement) {
        this.statement = statement;
        this.expression = expression;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        IStmt converted = new CompStmt(statement, new WhileStmt(expression, statement));
        state.getStk().push(converted);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typeExpression = expression.typecheck(typeEnv);
        if (typeExpression.equals(new BoolType())) {
            statement.typecheck(typeEnv.deepCopy());
            return typeEnv;
        } else
            throw new MyException("Condition in the do while statement must be bool!");
    }

    @Override
    public IStmt deepCopy() {
        return new DoWhileStmt(expression.deepCopy(), statement.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("do {%s} while (%s)", statement, expression);
    }
}
