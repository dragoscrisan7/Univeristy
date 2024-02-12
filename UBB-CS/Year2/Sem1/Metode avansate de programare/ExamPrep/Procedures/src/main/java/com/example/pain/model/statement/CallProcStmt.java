package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.*;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.Value;

import java.util.List;

public class CallProcStmt implements IStmt{
    private final String procedureName;
    private final List<Exp> expressions;

    public CallProcStmt(String procedureName, List<Exp> expressions) {
        this.procedureName = procedureName;
        this.expressions = expressions;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getTopSymTable();
        MyIHeap heap = state.getHeap();
        MyIProcTable procTable = state.getProcTable();
        if (procTable.isDefined(procedureName)) {
            List<String> variables = procTable.lookUp(procedureName).getKey();
            IStmt statement = procTable.lookUp(procedureName).getValue();
            MyIDictionary<String, Value> newSymTable = new MyDictionary<>();
            for(String var: variables) {
                int ind = variables.indexOf(var);
                newSymTable.put(var, expressions.get(ind).eval(symTable, heap));
            }
            state.getSymTable().push(newSymTable);
            state.getStk().push(new ReturnStmt());
            state.getStk().push(statement);
        } else {
            throw new MyException("Procedure not defined!");
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new CallProcStmt(procedureName, expressions);
    }

    @Override
    public String toString() {
        return String.format("call %s%s", procedureName, expressions.toString());
    }
}
