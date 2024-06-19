package com.example.pain.model.adt;

import com.example.pain.exception.MyException;

import java.util.HashMap;

public interface MyILatchTable<T1,T2> {
    int getFreeAddress();
    void setFreeAddress(int freeAddress);
    HashMap<Integer, Integer> getContent();
    void setContent(HashMap<Integer, Integer> newMap);
    boolean containsKey(Integer position);
    void put(Integer key, Integer value) throws MyException;
    void update(Integer position, Integer value) throws MyException;

    int get(Integer position) throws MyException;
}
