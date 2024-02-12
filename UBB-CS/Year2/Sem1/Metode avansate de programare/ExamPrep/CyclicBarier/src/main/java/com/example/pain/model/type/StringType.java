package com.example.pain.model.type;

import com.example.pain.model.value.StringValue;
import com.example.pain.model.value.Value;

public class StringType implements Type{

    public boolean equals(Object another){
        return another instanceof StringType;
    }

    public String toString(){
        return "string";
    }
    public Value defaultValue() { return new StringValue("");}

    public Type deepCopy(){return new StringType();}
}
