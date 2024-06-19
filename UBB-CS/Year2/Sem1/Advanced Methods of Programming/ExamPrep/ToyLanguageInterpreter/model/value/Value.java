package model.value;

import model.type.Type;

public interface Value {
    Type getType();
    boolean equals(Value anotherValue);
    Value deepCopy();
}
