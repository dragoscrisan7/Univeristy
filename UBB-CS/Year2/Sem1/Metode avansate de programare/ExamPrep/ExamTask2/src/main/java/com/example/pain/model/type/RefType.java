package com.example.pain.model.type;

import com.example.pain.model.value.RefValue;
import com.example.pain.model.value.Value;

public class RefType implements Type{
    Type inner;
    public RefType(Type inner) {this.inner=inner;}

    public Type getInner() {return inner;}

    public boolean equals(Object another){
        if (another instanceof RefType)
            return inner.equals(((RefType) another).getInner());
        else
            return false;
    }
    public String toString() { return "Ref(" +inner.toString()+")";}
    public Value defaultValue() { return new RefValue(0,inner);}

    public Type deepCopy() {
        return new RefType(inner.deepCopy());
    }
}
