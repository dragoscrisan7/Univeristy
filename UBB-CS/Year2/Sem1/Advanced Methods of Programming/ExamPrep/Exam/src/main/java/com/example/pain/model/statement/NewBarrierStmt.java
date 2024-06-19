package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIBarrierTable;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.Value;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewBarrierStmt implements IStmt{
    private final String var;
    private final Exp exp;
    private static final Lock lock = new ReentrantLock();

    public NewBarrierStmt(String var, Exp expression) {
        this.var = var;
        this.exp = expression;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        MyIBarrierTable barrierTable = state.getBarrierTable();
        IntValue number = (IntValue) (exp.eval(symTable, heap));
        int nr = number.getVal();
        int newFreeLocation = barrierTable.getNewFreeLocation();
        barrierTable.put(newFreeLocation, new Pair<>(nr, new ArrayList<>()));
        if (symTable.isDefined(var))
            symTable.update(var, new IntValue(newFreeLocation));
        else
            throw new MyException(String.format("%s is not defined in the symbol table!", var));
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (typeEnv.lookup(var).equals(new IntType()))
            if (exp.typecheck(typeEnv).equals(new IntType()))
                return typeEnv;
            else
                throw new MyException("Expression is not of type int!");
        else
            throw new MyException("Variable is not of type int!");
    }

    @Override
    public IStmt deepCopy() {
        return new NewBarrierStmt(var, exp.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("newBarrier(%s, %s)", var, exp);
    }

}
