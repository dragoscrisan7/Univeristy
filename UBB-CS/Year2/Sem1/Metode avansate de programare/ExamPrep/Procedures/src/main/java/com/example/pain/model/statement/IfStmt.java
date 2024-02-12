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

public class IfStmt implements IStmt {
    Exp exp;
    IStmt thenS;
    IStmt elseS;

    public IfStmt(Exp e, IStmt t, IStmt el) {exp=e; thenS=t;elseS=el;}

    public IStmt deepCopy() {
        return new IfStmt(exp.deepCopy(), thenS.deepCopy(), elseS.deepCopy());
    }

    public String toString(){ return "(IF("+ exp.toString()+") THEN(" +thenS.toString()
            +")ELSE("+elseS.toString()+"))";}
    public PrgState execute(PrgState state) throws MyException {
        Value result = this.exp.eval(state.getSymTable(), state.getHeap());
        if (result instanceof BoolValue boolResult) {
            IStmt statement;
            if (boolResult.getVal()) {
                statement = thenS;
            } else {
                statement = elseS;
            }

            MyIStack<IStmt> stack = state.getStk();
            stack.push(statement);
            state.setExeStack(stack);
            return null;
        } else {
            throw new MyException("Please provide a boolean expression in an if statement.");
        }
    }
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String,Type> typeEnv) throws
            MyException{
        Type typexp=exp.typecheck(typeEnv);
        if (typexp.equals(new BoolType())) {
            thenS.typecheck(typeEnv.deepCopy());
            elseS.typecheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new MyException("The condition of IF has not the type bool");
    }
}