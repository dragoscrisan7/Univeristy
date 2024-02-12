package com.example.pain.model.adt;

import com.example.pain.exception.MyException;

import java.util.HashMap;

public class MyLatchTable<T1,T2> implements MyILatchTable<T1,T2>{
    HashMap<Integer, Integer> latchTable;
    private int freeLocation = 0;

    public MyLatchTable(){
        this.latchTable = new HashMap<>();
    }
    @Override
    public boolean containsKey(Integer position) {
        return this.latchTable.containsKey(position);
    }

    @Override
    public HashMap<Integer, Integer> getContent() {
        synchronized (this) {
            return latchTable;
        }
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
    public void setContent(HashMap<Integer, Integer> newMap) {
        synchronized (this) {
            latchTable = newMap;
        }
    }

    @Override
    public void put(Integer key, Integer value) {
        synchronized (this){
            if(!latchTable.containsKey(key)){
                latchTable.put(key,value);
            }
            else{
                throw new MyException(String.format("Key %d already exists!", key));
            }
        }
    }

    @Override
    public void update(Integer position, Integer value) throws MyException {
        synchronized (this){
            if(!latchTable.containsKey(position))
                throw new MyException(String.format("Key %d doesnt exists!", position));
            else{
                latchTable.replace(position,value);
            }
        }
    }

    @Override
    public int get(Integer position) throws MyException {
        synchronized (this){
            if(latchTable.containsKey(position))
                return latchTable.get(position);
            else
                throw new MyException(String.format("Key %d doesnt exists!", position));
        }
    }
    @Override
    public String toString() {
        return latchTable.toString();
    }

}
