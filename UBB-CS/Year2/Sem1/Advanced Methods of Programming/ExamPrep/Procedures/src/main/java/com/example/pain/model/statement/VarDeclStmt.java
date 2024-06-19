package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.MyIStack;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.Value;

public class VarDeclStmt implements IStmt {
    String name;
    Type typ;

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public Type getTyp() {
        return typ;
    }
    public void setTyp(Type typ) {
        this.typ = typ;
    }

    public VarDeclStmt(String name, Type type) {
        this.name = name;
        this.typ = type;
    }


    public PrgState execute(PrgState state) throws MyException {
        MyIStack<MyIDictionary<String, Value>> symTable = state.getSymTable();
        MyIDictionary<String, Value> currentSymbolTable = symTable.peek();
        if (currentSymbolTable.isDefined(name)) {
            throw new MyException("Variable " + name + " already exists in the symTable.");
        }
        currentSymbolTable.put(name, typ.defaultValue());
        state.setSymTable(symTable);
        return null;
    }

    public String toString() {
        return name + " is " + typ;
    }
    public IStmt deepCopy() {
        return new VarDeclStmt(name, typ.deepCopy());
    }

    public MyIDictionary<String,Type> typecheck(MyIDictionary<String,Type> typeEnv) throws
            MyException{
        typeEnv.add(name,typ);
        return typeEnv;
    }
}