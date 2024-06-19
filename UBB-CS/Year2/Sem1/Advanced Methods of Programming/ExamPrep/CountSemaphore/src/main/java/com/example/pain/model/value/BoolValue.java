package com.example.pain.model.value;

import com.example.pain.model.type.BoolType;
import com.example.pain.model.type.Type;

public class BoolValue implements Value {
    boolean val;

    public BoolValue(boolean v) { val = v;}

    public boolean getVal() { return val;}

    public String toString() { return "bool(" + val + ")";}

    public Type getType(){ return new BoolType(); }

    public Value deepCopy() {
        return new BoolValue(val);
    }

    public boolean equals(Object differentValue) {
        if(!(differentValue instanceof BoolValue newValue))
            return false;
        return this.val == newValue.val;
    }
}