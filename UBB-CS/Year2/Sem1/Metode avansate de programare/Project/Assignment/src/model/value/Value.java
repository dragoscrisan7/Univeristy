package model.value;

import model.type.Type;

public interface Value {
        Type getType();
        Value deepCopy();

        boolean equals(Object diff_value);
}
