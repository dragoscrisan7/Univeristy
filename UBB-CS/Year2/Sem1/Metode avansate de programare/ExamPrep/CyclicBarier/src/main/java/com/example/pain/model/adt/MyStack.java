package com.example.pain.model.adt;
import com.example.pain.exception.MyException;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class MyStack<T> implements MyIStack<T>{
    ArrayList<T> stack;

    public MyStack(){
        stack = new ArrayList<T>();
    }

    public T pop() throws MyException {
        if(stack.size() == 0)
            throw new MyException("Stack is empty");
        T v = stack.get(stack.size() - 1);
        stack.remove(stack.size() -1);
        return v;
    }
    public void push(T v){
        stack.add(v);
    }

    public String toString() {
        return "" + stack;
    }
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public List<T> getReversed() {
        List<T> list = Arrays.asList((T[]) stack.toArray());
        Collections.reverse(list);
        return list;
    }
}
