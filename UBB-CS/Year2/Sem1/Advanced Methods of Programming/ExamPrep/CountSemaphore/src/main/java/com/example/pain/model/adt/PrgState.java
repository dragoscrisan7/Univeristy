package com.example.pain.model.adt;

import com.example.pain.exception.MyException;
import com.example.pain.model.statement.IStmt;
import com.example.pain.model.value.Value;

import java.io.BufferedReader;
import java.util.List;

public class PrgState {
    MyIStack<IStmt> exeStack;
    MyIDictionary<String, Value> symTable;
    MyIList<Value> out;
    IStmt originalProgram; //optional field, but good to have
    private MyIHeap heap;
    MyIDictionary<String, BufferedReader> fileTable;

    private MyISemaphore semaphore;
    private int id;
    private static int lastId = 0;

    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value>
            out, MyIDictionary<String, BufferedReader> fileTable, MyISemaphore semaphore, MyIHeap heap){
        this.exeStack=stk;
        this.symTable=symtbl;
        this.out = out;
        this.fileTable = fileTable;
        this.semaphore = semaphore;
        this.heap = heap;
        this.id = setId();
    }
    public PrgState(MyIStack<IStmt> stack, MyIDictionary<String,Value> symTable, MyIList<Value> out, MyIDictionary<String, BufferedReader> fileTable, MyISemaphore semaphore,MyIHeap heap, IStmt program) {
        this.exeStack = stack;
        this.symTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
        this.semaphore = semaphore;
        this.heap = heap;
        this.originalProgram = program.deepCopy();
        this.exeStack.push(this.originalProgram);
        this.id = setId();
    }

    public synchronized int setId() {
        lastId++;
        return lastId;
    }

    private IStmt deepCopy(IStmt prg) {
        return prg;
    }

    public MyIStack<IStmt> getStk() {return exeStack;}
    public void setExeStack(MyIStack<IStmt> exeStack) {
        this.exeStack = exeStack;
    }

    public MyIDictionary<String, Value> getSymTable() {return symTable;}
    public void setSymTable(MyIDictionary<String, Value> symTable) {
        this.symTable = symTable;
    }

    public MyIList<Value> getOut() {
        return out;
    }
    public void setOut(MyIList<Value> out) {
        this.out = out;
    }

    public IStmt getOriginalProgram() {
        return originalProgram;
    }
    public void setOriginalProgram(IStmt originalProgram) {
        this.originalProgram = originalProgram;
    }

    public MyIHeap getHeap() {return heap;}
    public void setHeap(MyIHeap newHeap) {this.heap = newHeap;}

    public boolean isNotCompleted() {
        return exeStack.isEmpty();
    }
    public MyIDictionary<String, BufferedReader> getFileTable() {
        return fileTable;
    }
    public void setFileTable(MyIDictionary<String, BufferedReader> newFileTable) {
        this.fileTable = newFileTable;
    }

    public MyISemaphore getSemaphore() {
        return semaphore;
    }
    public void setSemaphore(MyISemaphore newSemaphoreTable) {
        this.semaphore = newSemaphoreTable;
    }

    @Override
    public String toString() {
        return  "Id: " + id +
                "\nExecution stack: \n" + exeStack.toString() +
                "\nSymbol table: \n" + symTable.toString() +
                "\nOutput list: \n" + out.toString() + "" +
                "\nFile table:\n" + fileTable.toString() +
                "\nHeap:\n" + heap.toString() +
                "\nSemaphore table:\n" + semaphore.toString() + "\n";
    }

    public PrgState oneStep() throws MyException {
        if (exeStack.isEmpty())
            throw new MyException("Program state stack is empty!");
        IStmt currentStatement = exeStack.pop();
        return currentStatement.execute(this);
    }

    public String exeStackToString() {
        StringBuilder exeStackStringBuilder = new StringBuilder();
        List<IStmt> stack = exeStack.getReversed();
        for (IStmt statement: stack) {
            exeStackStringBuilder.append(statement.toString()).append("\n");
        }
        return exeStackStringBuilder.toString();
    }

    public String symTableToString() throws MyException {
        StringBuilder symTableStringBuilder = new StringBuilder();
        for (String key: symTable.keySet()) {
            symTableStringBuilder.append(String.format("%s -> %s\n", key, symTable.lookup(key).toString()));
        }
        return symTableStringBuilder.toString();
    }

    public String outToString() {
        StringBuilder outStringBuilder = new StringBuilder();
        for (Value elem: out.getList()) {
            outStringBuilder.append(String.format("%s\n", elem.toString()));
        }
        return outStringBuilder.toString();
    }

    public String fileTableToString() {
        StringBuilder fileTableStringBuilder = new StringBuilder();
        for (String key: fileTable.keySet()) {
            fileTableStringBuilder.append(String.format("%s\n", key));
        }
        return fileTableStringBuilder.toString();
    }

    public String heapToString() throws MyException {
        StringBuilder heapStringBuilder = new StringBuilder();
        for (Object key: heap.keySet()) {
            heapStringBuilder.append(String.format("%d -> %s\n", key, heap.get(key)));
        }
        return heapStringBuilder.toString();
    }
    public String semaphoreTableToString() throws MyException {
        StringBuilder semaphoreTableStringBuilder = new StringBuilder();
        for (int key: semaphore.getContent().keySet()) {
            semaphoreTableStringBuilder.append(String.format("%d -> (%d, %s)\n", key, semaphore.get(key).getKey(), semaphore.get(key).getValue()));
        }
        return semaphoreTableStringBuilder.toString();
    }

    public String programStateToString() throws MyException {
        return "Id: " + id + "\nExecution stack: \n" + exeStackToString() + "Symbol table: \n" + symTableToString() + "Output list: \n" + outToString() + "File table:\n" + fileTableToString() + "Heap memory:\n" + heapToString() + "Semaphore table:\n" + semaphoreTableToString();
    }

    public int getId() {
        return this.id;
    }
}

