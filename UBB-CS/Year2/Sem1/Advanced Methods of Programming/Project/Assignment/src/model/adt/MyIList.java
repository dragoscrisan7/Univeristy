package model.adt;

import exception.MyException;

import java.util.List;

public interface MyIList<T> {
    void add(T v);

    void remove() throws MyException;

    boolean isEmpty();
    List<T> getList();
}
