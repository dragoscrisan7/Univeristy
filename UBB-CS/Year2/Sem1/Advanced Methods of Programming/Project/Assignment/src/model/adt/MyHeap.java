package model.adt;

import exception.MyException;
import model.value.Value;

import java.util.HashMap;
import java.util.Set;

public class MyHeap<T1, T2> implements MyIHeap<T1, T2>{
    HashMap<Integer, Value> heap;
    Integer freeLocationValue;

    public MyHeap() {
        this.heap = new HashMap<>();
        freeLocationValue = 1;
    }
    @Override
    public HashMap<Integer, Value> getContent() {
        return heap;
    }
    @Override
    public void setContent(HashMap<Integer, Value> newMap) {
        this.heap = newMap;
    }

    @Override
    public boolean containsKey(Integer position) {
        return this.heap.containsKey(position);
    }

    public int newValue() {
        freeLocationValue += 1;
        while (freeLocationValue == 0 || heap.containsKey(freeLocationValue))
            freeLocationValue += 1;
        return freeLocationValue;
    }

    @Override
    public int getFreeValue() {
        return freeLocationValue;
    }

    @Override
    public int add(Value value) {
        heap.put(freeLocationValue, value);
        Integer toReturn = freeLocationValue;
        freeLocationValue = newValue();
        return toReturn;
    }

    @Override
    public void remove(Integer key) throws MyException {
        if (!containsKey(key))
            throw new MyException(key + " is not defined.");
        if(freeLocationValue > key){
            freeLocationValue = key;
        }
        this.heap.remove(key);
    }

    @Override
    public void update(Integer position, Value value) throws MyException {
        if (!heap.containsKey(position))
            throw new MyException(String.format("%d is not present in the heap", position));
        heap.replace(position, value);
    }
    @Override
    public Value get(Object position) throws MyException {
        if (!heap.containsKey(position))
            throw new MyException(String.format("%d is not present in the heap", position));
        return heap.get(position);
    }

    @Override
    public Set<Integer> keySet() {
        synchronized (this) {
            return heap.keySet();
        }
    }
    @Override
    public String toString() {
        return this.heap.toString();
    }
}
