package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.adt.MyILatchTable;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.Value;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class newLatchStmt implements IStmt{
    String var;
    Exp expression;
    private static final Lock lock = new ReentrantLock();


    public newLatchStmt(String var, Exp expression) {
        this.var = var;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        MyILatchTable latchTable = state.getLatchTable();
        IntValue nr = (IntValue) (expression.eval(symTable, heap));
        int number = nr.getVal();
        int freeAddress = latchTable.getFreeAddress();
        latchTable.put(freeAddress, number);
        if (symTable.isDefined(var)) {
            symTable.update(var, new IntValue(freeAddress));
        } else {
            throw new MyException(String.format("%s is not defined in the symTable!", var));
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (typeEnv.lookup(var).equals(new IntType())) {
            if (expression.typecheck(typeEnv).equals(new IntType())) {
                return typeEnv;
            } else {
                throw new MyException("Expression doesn't have the int type!");
            }
        } else {
            throw new MyException(String.format("%s is not int!", var));
        }
    }

    @Override
    public IStmt deepCopy() {
        return new newLatchStmt(var, expression.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("newLatch(%s, %s)", var, expression);
    }
}
