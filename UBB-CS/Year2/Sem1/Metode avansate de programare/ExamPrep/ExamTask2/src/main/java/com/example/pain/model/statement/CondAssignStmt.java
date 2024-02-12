package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIStack;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.expression.VarExp;
import com.example.pain.model.type.BoolType;
import com.example.pain.model.type.Type;

public class CondAssignStmt implements IStmt{
    private final String var;
    private final Exp expression1;
    private final Exp expression2;
    private final Exp expression3;

    public CondAssignStmt(String variable, Exp expression1, Exp expression2, Exp expression3) {
        this.var = variable;
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.expression3 = expression3;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> exeStack = state.getStk();
        IStmt converted = new IfStmt(expression1, new AssignStmt(var, expression2), new AssignStmt(var, expression3));
        exeStack.push(converted);
        state.setExeStack(exeStack);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type variableType = new VarExp(var).typecheck(typeEnv);
        Type type1 = expression1.typecheck(typeEnv);
        Type type2 = expression2.typecheck(typeEnv);
        Type type3 = expression3.typecheck(typeEnv);
        if (type1.equals(new BoolType()) && type2.equals(variableType) && type3.equals(variableType))
            return typeEnv;
        else
            throw new MyException("The conditional assignment is invalid!");
    }

    @Override
    public IStmt deepCopy() {
        return new CondAssignStmt(var, expression1.deepCopy(), expression2.deepCopy(), expression3.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("%s=(%s)? %s: %s", var, expression1, expression2, expression3);
    }
}
