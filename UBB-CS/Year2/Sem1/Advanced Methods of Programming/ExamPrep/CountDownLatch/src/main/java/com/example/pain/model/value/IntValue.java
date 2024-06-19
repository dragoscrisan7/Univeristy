package com.example.pain.model.value;

import com.example.pain.model.type.IntType;
import com.example.pain.model.type.Type;

public class  IntValue implements Value{
    int val;
    public IntValue(int v){
        val=v;
    }

    public int getVal() {return val;}

    @Override
    public Value deepCopy() {
        return new IntValue(val);
    }

    public boolean equals(Object differentValue) {
        if(!(differentValue instanceof IntValue newValue))
            return false;
        return newValue.val == this.val;
    }

    @Override
    public String toString() {
        return "int(" + this.val + ")";
    }
    @Override
    public Type getType() {
        return new IntType();
    }
}
