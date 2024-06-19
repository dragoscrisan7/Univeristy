package com.example.pain.model.type;

import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.Value;

public class IntType implements Type {

    public boolean equals(Object another){
        return another instanceof IntType;
    }
    public String toString() { return "int";}
    public Value defaultValue() {
        return new IntValue(0);
    }

    public Type deepCopy() {
        return new IntType();
    }
}
