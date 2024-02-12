package com.example.pain.model.statement;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.MyIDictionary;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.expression.Exp;
import com.example.pain.model.type.IntType;
import com.example.pain.model.type.StringType;
import com.example.pain.model.type.Type;
import com.example.pain.model.value.IntValue;
import com.example.pain.model.value.StringValue;
import com.example.pain.model.value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements  IStmt{

    Exp exp;

    String var_name;

    public ReadFile(Exp e, String var_name){
        exp = e;
        this.var_name = var_name;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();

        if(symTable.isDefined(var_name)){
            Value v = symTable.lookup(var_name);
            if(v.getType().equals(new IntType())){
                Value expv = exp.eval(symTable, state.getHeap());
                if(expv.getType().equals(new StringType())){
                    StringValue sv = (StringValue) expv;
                    if(fileTable.isDefined(sv.getVal())){
                        BufferedReader br =fileTable.lookup(sv.getVal());
                        try{
                            String line = br.readLine();
                            if(line == null)
                                line = "0";
                            symTable.add(var_name, new IntValue(Integer.parseInt(line)));
                        } catch (IOException e) {
                            throw new MyException(String.format("Could not read from file %s", sv));
                        }
                    }
                    else{throw new MyException(String.format("The file table does not contain %s", sv));}
                }
                else{throw new MyException(String.format("%s does not evaluate to StringType", v));}
            }
            else{throw new MyException(String.format("%s is not of type IntType", v));}
        }
        else{throw new MyException(String.format("%s is not present in the symTable.", var_name));}
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new ReadFile(exp.deepCopy(), var_name);
    }
    public String toString() {
        return String.format("ReadFile(%s, %s)", exp.toString(), var_name);
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        if (exp.typecheck(typeEnv).equals(new StringType()))
            if (typeEnv.lookup(var_name).equals(new IntType()))
                return typeEnv;
            else
                throw new MyException("ReadFile requires an int as its variable parameter.");
        else
            throw new MyException("ReadFile requires a string as es expression parameter.");
    }
}
