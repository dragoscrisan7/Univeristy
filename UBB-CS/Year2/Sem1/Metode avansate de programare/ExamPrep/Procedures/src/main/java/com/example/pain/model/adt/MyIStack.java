package com.example.pain.model.adt;

import com.example.pain.exception.MyException;

import java.util.List;

public interface MyIStack<T>{
    T pop() throws MyException;
    void push(T v);
    T peek() throws MyException;

    boolean isEmpty();

    List<T> getReversed();
    MyIStack<T> clone();
}
