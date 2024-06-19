package com.example.pain.model.value;

import com.example.pain.model.type.Type;

public interface Value {
        Type getType();
        Value deepCopy();

        boolean equals(Object diff_value);
}
