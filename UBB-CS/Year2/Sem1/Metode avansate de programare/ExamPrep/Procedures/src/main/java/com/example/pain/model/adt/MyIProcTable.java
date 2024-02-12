package com.example.pain.model.adt;

import com.example.pain.exception.MyException;
import com.example.pain.model.statement.IStmt;
import javafx.util.Pair;

import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Set;

public interface MyIProcTable {
    boolean isDefined(String key);
    void put(String key, Pair<List<String>, IStmt> value);
    Pair<List<String>, IStmt> lookUp(String key) throws MyException;
    void update(String key,  Pair<List<String>, IStmt> value) throws MyException;
    Collection< Pair<List<String>, IStmt>> values();
    void remove(String key) throws MyException;
    Set<String> keySet();
    HashMap<String,  Pair<List<String>, IStmt>> getContent();
    MyIDictionary<String, Pair<List<String>, IStmt>> deepCopy() throws MyException;
}
