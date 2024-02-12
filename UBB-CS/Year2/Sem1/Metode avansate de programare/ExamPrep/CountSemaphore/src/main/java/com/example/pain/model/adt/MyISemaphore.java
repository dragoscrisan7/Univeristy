package com.example.pain.model.adt;

import com.example.pain.exception.MyException;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;

public interface MyISemaphore {
    int getFreeAddress();
    void setFreeAddress(int freeAddress);
    HashMap<Integer, Pair<Integer, List<Integer>>> getContent();
    void setContent(HashMap<Integer, Pair<Integer, List<Integer>>> newMap);
    boolean containsKey(Integer position);
    void put(Integer key, Pair<Integer, List<Integer>> value) throws MyException;
    void update(Integer position, Pair<Integer, List<Integer>> value) throws MyException;

    Pair<Integer, List<Integer>> get(Integer position) throws MyException;
}
