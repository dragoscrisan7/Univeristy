package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyILatchTable;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.Value;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class AwaitStmt implements IStmt{

    private String var;

    private static final Lock lock = new ReentrantLock();

    public AwaitStmt(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyILatchTable<Integer, Integer> latchTable = state.getLatchTable();
        if(symTable.isDefined(var)){
            IntValue intvl = (IntValue) symTable.lookup(var);
            int addres = intvl.getVal();
            if(latchTable.containsKey(addres)){
                if (latchTable.get(addres) != 0) {
                    state.getStk().push(this);
                }
            }
            else{
                throw new MyException("Latch table doesn't have addres!");
            }
        }
        else{
            throw new MyException("Variable is not defined");
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if(typeEnv.lookup(var).equals(new IntType())){
            return typeEnv;
        }
        else
            throw new MyException(String.format("%s is not int!", var));
    }

    @Override
    public IStmt deepCopy() {
        return new AwaitStmt(this.var);
    }
    @Override
    public String toString() {
        return String.format("await(%s)", var);
    }
}
