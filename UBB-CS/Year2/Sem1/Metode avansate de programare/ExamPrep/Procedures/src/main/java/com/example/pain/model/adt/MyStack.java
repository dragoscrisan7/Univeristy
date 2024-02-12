package com.example.pain.model.adt;
import com.example.pain.exception.MyException;

import java.util.*;

public class MyStack<T> implements MyIStack<T>{
    Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<>();
    }

    public MyStack(Stack<T> stack) {
        this.stack = stack;
    }

    public T pop() throws MyException {
        if (stack.isEmpty())
            throw new MyException("Stack is empty!");
        return this.stack.pop();
    }
    public void push(T v){
        this.stack.push(v);;
    }

    public String toString() {
        return "" + stack;
    }
    @Override
    public T peek() throws MyException {
        if (stack.isEmpty())
            throw new MyException("Stack is empty!");
        return this.stack.peek();
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
    @Override
    public MyIStack<T> clone() {
        return new MyStack<T>((Stack<T>)stack.clone());
    }
}
