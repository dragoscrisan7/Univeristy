package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIToySemaphore;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.adt.Tuple;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.Value;

import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class AcquireStmt implements IStmt{
    private final String var;
    private static final Lock lock = new ReentrantLock();

    public AcquireStmt(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIToySemaphore semaphoreTable = state.getToySemaphore();
        if (symTable.isDefined(var)) {
            if (symTable.lookup(var).getType().equals(new IntType())) {
                IntValue fi = (IntValue) symTable.lookup(var);
                int foundIndex = fi.getVal();
                if (semaphoreTable.containsKey(foundIndex)) {
                    Tuple<Integer, List<Integer>, Integer> foundSemaphore = semaphoreTable.get(foundIndex);
                    int NL = foundSemaphore.getSecond().size();
                    int N1 = foundSemaphore.getFirst();
                    int N2 = foundSemaphore.getThird();
                    if ((N1 - N2) > NL) {
                        if (!foundSemaphore.getSecond().contains(state.getId())) {
                            foundSemaphore.getSecond().add(state.getId());
                            semaphoreTable.update(foundIndex, new Tuple<>(N1, foundSemaphore.getSecond(), N2));
                        }
                    } else {
                        state.getStk().push(this);
                    }
                } else {
                    throw new MyException("Index is not in the semaphore table!");
                }
            } else {
                throw new MyException("Index does not have the int type!");
            }
        } else
            throw new MyException("Index not in the symbol table!");
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new AcquireStmt(var);
    }

    @Override
    public String toString() {
        return String.format("acquire(%s)", var);
    }
}
