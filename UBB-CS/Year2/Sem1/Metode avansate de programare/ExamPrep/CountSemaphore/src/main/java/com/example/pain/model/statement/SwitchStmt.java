package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIStack;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.type.BoolType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.Value;

public class SwitchStmt implements IStmt{

    Exp exp, exp1, exp2;
    IStmt stm1, stm2, stm3;

    public SwitchStmt(Exp exp, Exp exp1, Exp exp2, IStmt stm1, IStmt stm2, IStmt stm3) {
        this.exp = exp;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.stm1 = stm1;
        this.stm2 = stm2;
        this.stm3 = stm3;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        Value result = this.exp.eval(state.getSymTable(), state.getHeap());
        Value result1 = this.exp1.eval(state.getSymTable(), state.getHeap());
        Value result2 = this.exp2.eval(state.getSymTable(), state.getHeap());
        IStmt statement;
        if(result.equals(result1)){
            statement = stm1;
        }
        else if(result.equals(result2)){
            statement = stm2;
        }
        else{
            statement = stm3;
        }
        MyIStack<IStmt> stack = state.getStk();
        stack.push(statement);
        state.setExeStack(stack);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp=exp.typecheck(typeEnv);
        Type typexp1=exp1.typecheck(typeEnv);
        Type typexp2=exp2.typecheck(typeEnv);
        if (typexp.equals(typexp1) && typexp.equals(typexp2)) {
            stm1.typecheck(typeEnv.deepCopy());
            stm2.typecheck(typeEnv.deepCopy());
            stm3.typecheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new MyException("The expressions should have the same type");
    }

    @Override
    public IStmt deepCopy() {
        return new SwitchStmt(exp.deepCopy(),exp1.deepCopy(),exp2.deepCopy(), stm1.deepCopy(),stm2.deepCopy(),stm3.deepCopy());
    }
    public String toString(){ return "(Switch("+ exp.toString()+") {(" + exp1.toString()
            +" do "+stm1.toString()+")" + " (" + exp2.toString() +" do " + stm2.toString() +
            ") (else do " + stm3.toString() + ")}" + ")";}
}
