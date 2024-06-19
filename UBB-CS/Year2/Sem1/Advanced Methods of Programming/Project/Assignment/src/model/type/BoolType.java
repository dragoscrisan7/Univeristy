package model.type;

import model.value.BoolValue;
import model.value.Value;

public class BoolType implements Type {
    public boolean equals(Object another){
        return another instanceof BoolType;
    }

    public String toString() {
        return "boolean";
    }

    public Value defaultValue() {
        return new BoolValue(false);
    }

    public Type deepCopy() {
        return new BoolType();
    }
}
