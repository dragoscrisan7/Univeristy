package com.example.pain.model.adt;

import com.example.pain.exception.MyException;

import java.util.HashMap;
import java.util.List;

public interface MyIToySemaphore {
    void put(int key, Tuple<Integer, List<Integer>, Integer> value) throws MyException;
    Tuple<Integer, List<Integer>, Integer> get(int key) throws MyException;
    boolean containsKey(int key);
    int getFreeAddress();
    void setFreeAddress(int freeAddress);
    void update(int key, Tuple<Integer, List<Integer>, Integer> value) throws MyException;
    HashMap<Integer, Tuple<Integer, List<Integer>, Integer>> getToySemaphoreTable();
    void setToySemaphoreTable(HashMap<Integer, Tuple<Integer, List<Integer>, Integer>> newToySemaphoreTable);
}
