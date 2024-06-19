package model.adt;

import exception.MyException;
import model.value.Value;

import java.util.HashMap;
import java.util.Set;

public interface MyIHeap<T1, T2> {
    int getFreeValue();
    HashMap<Integer, Value> getContent();
    void setContent(HashMap<Integer, Value> newMap);
    int add(Value value);
    void update(Integer position, Value value) throws MyException;
    Value get(Object position) throws MyException;
    boolean containsKey(Integer position);
    void remove(Integer key) throws MyException;
    Set<Integer> keySet();
}
