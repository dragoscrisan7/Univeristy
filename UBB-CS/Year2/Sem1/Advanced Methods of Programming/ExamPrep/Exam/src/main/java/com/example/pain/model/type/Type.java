package com.example.pain.model.type;

import com.example.pain.model.value.Value;

public interface Type{

    boolean equals(Object another);
    Value defaultValue();

    Type deepCopy();
}
