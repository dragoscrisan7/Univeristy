package com.example.pain.model.adt;

import com.example.pain.exception.MyException;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;

public class MySemaphore implements MyISemaphore{
    private HashMap<Integer, Pair<Integer, List<Integer>>> semaphore;
    private int freeLocation = 0;


    public MySemaphore() {
        this.semaphore = new HashMap<>();
    }

    @Override
    public int getFreeAddress() {
        synchronized (this) {
            freeLocation++;
            return freeLocation;
        }
    }

    @Override
    public void setFreeAddress(int freeAddress) {
        synchronized (this) {
            this.freeLocation = freeAddress;
        }
    }

    @Override
    public HashMap<Integer, Pair<Integer, List<Integer>>> getContent() {
        synchronized (this) {
            return semaphore;
        }
    }

    @Override
    public void setContent(HashMap<Integer, Pair<Integer, List<Integer>>> newMap) {
        synchronized (this){
            this.semaphore = newMap;
        }
    }

    @Override
    public boolean containsKey(Integer position) {
        return this.semaphore.containsKey(position);
    }

    @Override
    public void put(Integer key, Pair<Integer, List<Integer>> value) throws MyException {
        synchronized (this){
            if(!semaphore.containsKey(key)){
                semaphore.put(key,value);
            }
            else{
                throw new MyException(String.format("Key %d already exists!", key));
            }
        }
    }

    @Override
    public void update(Integer position, Pair<Integer, List<Integer>> value) throws MyException {
        synchronized (this){
            if(!semaphore.containsKey(position))
                throw new MyException(String.format("Key %d doesnt exists!", position));
            else{
                semaphore.replace(position,value);
            }
        }
    }

    @Override
    public Pair<Integer, List<Integer>> get(Integer position) throws MyException {
        synchronized (this){
            if(semaphore.containsKey(position))
                return semaphore.get(position);
            else
                throw new MyException(String.format("Key %d doesnt exists!", position));
        }
    }
    @Override
    public String toString() {
        return semaphore.toString();
    }
}
