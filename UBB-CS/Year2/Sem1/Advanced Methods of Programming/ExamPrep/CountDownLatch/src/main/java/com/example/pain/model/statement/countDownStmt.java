package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyILatchTable;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.ValueExp;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.Value;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class countDownStmt implements IStmt{
    private String var;
    private static final Lock lock = new ReentrantLock();

    public countDownStmt(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyILatchTable<Integer, Integer> latchTable = state.getLatchTable();
        if (symTable.isDefined(var)) {
            IntValue fi = (IntValue) symTable.lookup(var);
            int i = fi.getVal();
            if (latchTable.containsKey(i)) {
                if (latchTable.get(i) > 0) {
                    latchTable.update(i, latchTable.get(i) - 1);
                }
                state.getStk().push(new PrintStmt(new ValueExp(new IntValue(state.getId()))));
            } else {
                throw new MyException("Index not found in the latch table!");
            }
        } else {
            throw new MyException("Variable not defined!");
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (typeEnv.lookup(var).equals(new IntType()))
            return typeEnv;
        else
            throw new MyException(String.format("%s is not int!", var));
    }

    @Override
    public IStmt deepCopy() {
        return new countDownStmt(var);
    }
    @Override
    public String toString() {
        return String.format("countDown(%s)", var);
    }
}
