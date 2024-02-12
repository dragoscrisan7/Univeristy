package model.adt;

import exception.MyException;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

public class MyDictionary<T1, T2> implements MyIDictionary<T1,T2>{

    HashMap<T1, T2> dict;

    public MyDictionary(){
        dict = new HashMap<>();
    }

    @Override
    public boolean isDefined(T1 id) {
        return dict.containsKey(id);
    }

    @Override
    public T2 lookup(T1 id) {
        return dict.get(id);
    }

    @Override
    public void update(T1 id, T2 val) {
        dict.replace(id, val);
    }

    public void add(T1 key, T2 val) {
        dict.put(key, val);
    }

    public T2 remove(T1 key) throws MyException {
        if(dict.size() == 0)
            throw new MyException("Empty dictionary");
        return dict.remove(key);
    }

    public String toString() {
        return "" + dict;
    }
    public Collection<T2> values() {
        return this.dict.values();
    }

    @Override
    public HashMap<T1, T2> getContent() {
        return dict;
    }
    @Override
    public void put(T1 key, T2 value) {
        this.dict.put(key, value);
    }

    @Override
    public Set<T1> keySet() {
        return dict.keySet();
    }

    @Override
    public MyIDictionary<T1, T2> deepCopy() throws MyException {
        MyIDictionary<T1, T2> toReturn = new MyDictionary<>();
        for (T1 key: keySet())
            toReturn.put(key, lookup(key));
        return toReturn;
    }
}
