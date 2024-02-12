package com.example.pain.model.expression;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIHeap;
import com.example.pain.model.type.RefType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.RefValue;
import com.example.pain.model.value.Value;

public class rH implements Exp{
    Exp e;

    public rH(Exp new_exp){
        e = new_exp;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer,Value> hp) throws MyException {
        Value v = e.eval(tbl, hp);
        if(v instanceof RefValue){
            RefValue rv = (RefValue) v;
            if(hp.containsKey(rv.getAddr())){
                return hp.get(rv.getAddr());
            }
            else{
                throw new MyException(String.format("The address is not defined on the heap!"));
            }
        }
        else{
            throw new MyException(String.format("%s not of RefType", v));
        }
    }

    @Override
    public Exp deepCopy() {
        return new rH(e.deepCopy());
    }

    public Exp getExp() {
        return e;
    }

    @Override
    public String toString() {
        return e.toString();
    }

    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException{
        Type typ=e.typecheck(typeEnv);
        if (typ instanceof RefType) {
            RefType reft =(RefType) typ;
            return reft.getInner();
        } else
            throw new MyException("the rH argument is not a Ref Type");
    }
}
