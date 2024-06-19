package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyISemaphore;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.Value;
import javafx.util.Pair;

import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class releaseStmt implements IStmt{
    private String var;
    private static final Lock lock = new ReentrantLock();
    public releaseStmt(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyISemaphore semaphoreTable = state.getSemaphore();
        if (symTable.isDefined(var)) {
            if (symTable.lookup(var).getType().equals(new IntType())) {
                IntValue fi = (IntValue) symTable.lookup(var);
                int foundIndex = fi.getVal();
                if (semaphoreTable.getContent().containsKey(foundIndex)) {
                    Pair<Integer, List<Integer>> foundSemaphore = semaphoreTable.get(foundIndex);
                    if (foundSemaphore.getValue().contains(state.getId()))
                        foundSemaphore.getValue().remove((Integer) state.getId());
                        semaphoreTable.update(foundIndex, new Pair<>(foundSemaphore.getKey(), foundSemaphore.getValue()));
                } else {
                    throw new MyException("Index not in the semaphore table!");
                }
            } else {
                throw new MyException("Index must be of int type!");
            }
        } else {
            throw new MyException("Index not in symbol table!");
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (typeEnv.lookup(var).equals(new IntType())) {
            return typeEnv;
        } else {
            throw new MyException(String.format("%s is not int!", var));
        }
    }

    @Override
    public IStmt deepCopy() {
        return new releaseStmt(var);
    }
    @Override
    public String toString() {
        return String.format("release(%s)", var);
    }
}
