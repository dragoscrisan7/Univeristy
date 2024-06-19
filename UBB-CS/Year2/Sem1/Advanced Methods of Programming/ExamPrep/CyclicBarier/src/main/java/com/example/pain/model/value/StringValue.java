package com.example.pain.model.value;

import com.example.pain.model.type.StringType;
import com.example.pain.model.type.Type;

public class StringValue implements Value{
    String s;

    public StringValue(String new_s){
        s= new_s;
    }

    public Type getType(){return new StringType();}

    public String toString(){return "'" + s + "'";}

    public Value deepCopy(){return new StringValue(s);}

    public boolean equals(Object differentValue) {
        if(!(differentValue instanceof StringValue newValue))
            return false;
        return this.s.equals(newValue.s);
    }

    public String getVal(){
        return s;
    }
}
