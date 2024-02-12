package com.example.pain.model.adt;

import com.example.pain.exception.MyException;

import java.util.ArrayList;
import java.util.List;

public class MyList <T> implements MyIList<T>{
    ArrayList<T> newList;

    public MyList(){
        newList = new ArrayList<T>();
    }

    @Override
    public void add(T v) {
        newList.add(v);
    }

    public void remove() throws MyException {
        if(newList.size() == 0)
            throw new MyException("List is already empty");
        newList.remove(newList.size()-1);
    }

    @Override
    public boolean isEmpty() {
        return this.newList.isEmpty();
    }

    @Override
    public List<T> getList() {
        return newList;
    }
    @Override
    public String toString(){
        return newList.toString();
    }
}
