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

public class AcquireStmt implements IStmt{
    private String var;
    private static final Lock lock = new ReentrantLock();

    public AcquireStmt(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyISemaphore semaphoreTable = state.getSemaphore();
        if(symTable.isDefined(var)){
            if(symTable.lookup(var).getType().equals(new IntType())){
                IntValue iv = (IntValue) symTable.lookup(var);
                int foundIndex = iv.getVal();
                if(semaphoreTable.containsKey(foundIndex)){
                    Pair<Integer, List<Integer>> foundSemaphore = semaphoreTable.get(foundIndex);
                    int NL = foundSemaphore.getValue().size();
                    int N1 = foundSemaphore.getKey();
                    if (N1 > NL) {
                        if (!foundSemaphore.getValue().contains(state.getId())) {
                            foundSemaphore.getValue().add(state.getId());
                            semaphoreTable.update(foundIndex, new Pair<>(N1, foundSemaphore.getValue()));
                        }
                    } else {
                        state.getStk().push(this);
                    }
                }
                else{
                    throw new MyException("Index not a key in the semaphore table!");
                }
            }
            else{
                throw new MyException("Index must be of int type!");
            }
        }
        else
            throw new MyException("Index not in symbol table!");
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
        return new AcquireStmt(var);
    }
    @Override
    public String toString() {
        return String.format("acquire(%s)", var);
    }
}
