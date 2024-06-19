package model.value;

import model.type.RefType;
import model.type.Type;

import java.util.Objects;

public class RefValue implements Value{
    int address;
    Type locationType;

    public RefValue(int i, Type inner) {
        address = i;
        locationType = inner;
    }

    public int getAddr() {return address;}

    public Type getLocationType() {
        return locationType;
    }

    public Type getType() { return new RefType(locationType);}

    @Override
    public Value deepCopy() {
        return new RefValue(address, locationType.deepCopy());
    }

    @Override
    public boolean equals(Object different_value) {
        if(!(different_value instanceof RefValue newRefValue))
            return false;
        return ((RefValue) different_value).getAddr() == address && ((RefValue) different_value).getType() == locationType;
    }

    @Override
    public String toString() {
        return String.format("(%d, %s)", address, locationType);
    }
}
