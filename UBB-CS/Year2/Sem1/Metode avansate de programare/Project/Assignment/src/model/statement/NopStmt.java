package model.statement;

import exception.MyException;
import model.adt.MyIDictionary;
import model.adt.PrgState;
import model.type.Type;

class NopStmt implements IStmt {
     public PrgState execute(PrgState state) throws MyException{
         return null;
     }
    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }

     public String toString(){return super.toString();}
     public IStmt deepCopy() {
        return new NopStmt();
    }
}