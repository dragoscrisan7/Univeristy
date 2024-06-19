package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyILockTable;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.Value;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class UnlockStmt implements IStmt{
    private final String var;
    private static final Lock lock = new ReentrantLock();

    public UnlockStmt(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyILockTable lockTable = state.getLockTable();
        if (symTable.isDefined(var)) {
            if (symTable.lookup(var).getType().equals(new IntType())) {
                IntValue fi = (IntValue) symTable.lookup(var);
                int foundIndex = fi.getVal();
                if (lockTable.containsKey(foundIndex)) {
                    if (lockTable.get(foundIndex) == state.getId())
                        lockTable.update(foundIndex, -1);
                } else {
                    throw new MyException("Index not in the lock table!");
                }
            } else {
                throw new MyException("Var is not of int type!");
            }
        } else {
            throw new MyException("Variable is not defined!");
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (typeEnv.lookup(var).equals(new IntType()))
            return typeEnv;
        else
            throw new MyException("Var is not of type int!");
    }

    @Override
    public IStmt deepCopy() {
        return new UnlockStmt(var);
    }

    @Override
    public String toString() {
        return String.format("unlock(%s)", var);
    }
}
