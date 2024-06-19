package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.adt.MyISemaphore;
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

public class createSemaphoreStmt implements IStmt{
    Exp exp;
    private String var;
    private static final Lock lock = new ReentrantLock();

    public createSemaphoreStmt(String var, Exp exp) {
        this.exp = exp;
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        MyISemaphore semaphoreTable = state.getSemaphore();
        IntValue nr = (IntValue) (exp.eval(symTable, heap));
        int number = nr.getVal();
        int freeAddress = semaphoreTable.getFreeAddress();
        semaphoreTable.put(freeAddress, new Pair<>(number, new ArrayList<>()));
        if (symTable.isDefined(var) && symTable.lookup(var).getType().equals(new IntType()))
            symTable.update(var, new IntValue(freeAddress));
        else
            throw new MyException(String.format("Variable %s should have the int type!", var));
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (typeEnv.lookup(var).equals(new IntType())) {
            if (exp.typecheck(typeEnv).equals(new IntType()))
                return typeEnv;
            else
                throw new MyException("Expression is not of int type!");
        } else {
            throw new MyException(String.format("%s is not of type int!", var));
        }
    }

    @Override
    public IStmt deepCopy() {
        return new createSemaphoreStmt(var, exp.deepCopy());
    }
    @Override
    public String toString() {
        return String.format("createSemaphore(%s, %s)", var, exp);
    }
}
