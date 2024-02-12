package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIStack;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.expression.RelExp;
import com.example.pain.model.expression.VarExp;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;

public class ForStmt implements IStmt{
    private final Exp exp1,exp2,exp3;
    private final String var;
    private final IStmt stmt;

    public ForStmt(String var, Exp exp1, Exp exp2, Exp exp3, IStmt stmt) {
        this.var = var;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
        this.stmt = stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> exeStack = state.getStk();
        IStmt forToWhileStmt = new CompStmt(new AssignStmt("v", exp1),
                new WhileStmt(new RelExp("<", new VarExp("v"), exp2),
                        new CompStmt(stmt, new AssignStmt("v", exp3))));
        exeStack.push(forToWhileStmt);
        state.setExeStack(exeStack);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type type1 = exp1.typecheck(typeEnv);
        Type type2 = exp2.typecheck(typeEnv);
        Type type3 = exp3.typecheck(typeEnv);

        if (type1.equals(new IntType()) && type2.equals(new IntType()) && type3.equals(new IntType()))
            return typeEnv;
        else
            throw new MyException("The for statement is invalid!");
    }

    @Override
    public IStmt deepCopy() {
        return new ForStmt(var,exp1.deepCopy(),exp2.deepCopy(),exp3.deepCopy(),stmt.deepCopy());
    }
    @Override
    public String toString() {
        return String.format("for(%s=%s; %s<%s; %s=%s) {%s}", var, exp1, var, exp2, var, exp3, stmt);
    }
}
