package model.adt;

import exception.MyException;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

public interface MyIDictionary <T1, T2>{

    T2 remove(T1 key) throws MyException;
    void add(T1 key, T2 val);
    boolean isDefined(T1 id);
    T2 lookup(T1 id);
    void update(T1 id, T2 val);
    Collection<T2> values();

    HashMap<T1, T2> getContent();
    void put(T1 key, T2 value);
    Set<T1> keySet();

    MyIDictionary<T1, T2> deepCopy() throws MyException;
}
