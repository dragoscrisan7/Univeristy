package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.type.RefType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.RefValue;
import com.example.pain.model.value.Value;

public class wH implements IStmt{
    String var_name;
    Exp e;

    public wH(String s, Exp new_e){
        var_name= s;
        e = new_e;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTbl= state.getSymTable();
        MyIHeap<Integer, Value> hp = state.getHeap();

        if(symTbl.isDefined(var_name)){
            Value v = symTbl.lookup(var_name);
            if(v.getType() instanceof RefType){
                RefValue rv = (RefValue) v;
                if(hp.containsKey(rv.getAddr())){
                    Value evaluated = e.eval(symTbl, hp);
                    if(evaluated.getType().equals(rv.getLocationType())){
                        hp.update(rv.getAddr(), evaluated);
                    }
                    else
                        throw new MyException(String.format("%s not of %s", evaluated, rv.getLocationType()));
                }
                else
                    throw new MyException(String.format("The RefValue %s is not defined in the heap", v));
            }
            else
                throw new MyException(String.format("%s not of RefType", v));
        }
        else
            throw new MyException(String.format("%s not present in the symTable", var_name));
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new wH(var_name, e.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("WriteHeap(%s, %s)", var_name, e);
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException{
        if (typeEnv.lookup(var_name).equals(new RefType(e.typecheck(typeEnv))))
            return typeEnv;
        else
            throw new MyException("WriteHeap: right hand side and left hand side have different types.");
    }
}
