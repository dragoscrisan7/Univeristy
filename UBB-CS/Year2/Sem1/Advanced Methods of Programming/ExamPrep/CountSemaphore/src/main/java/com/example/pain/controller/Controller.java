package com.example.pain.controller;

import com.example.pain.exception.MyException;
import com.example.pain.model.adt.PrgState;
import com.example.pain.model.value.RefValue;
import com.example.pain.model.value.Value;
import com.example.pain.repository.IRepository;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller implements IController {
    IRepository repo;
    ExecutorService executorService;
    boolean display_flag;

    public Controller(IRepository repo){
        this.repo = repo;
    }

    public ExecutorService getExecutor() {
        return executorService;
    }

    public void setDisplayFlag(boolean value) {
        this.display_flag = value;
    }

    public void oneStepForAllPrg(List<PrgState> programStates) throws MyException, InterruptedException {
        programStates.forEach(programState -> {
            try {
                repo.logPrgStateExec(programState);
                display(programState);
            } catch (IOException | MyException e) {
                System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
            }
        });
        List<Callable<PrgState>> callList = programStates.stream()
                .map((PrgState p) -> (Callable<PrgState>) (p::oneStep))
                .collect(Collectors.toList());

        List<PrgState> newProgramList = executorService.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
                    }
                    return null;
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList());

        programStates.addAll(newProgramList);

        programStates.forEach(programState -> {
            try {
                repo.logPrgStateExec(programState);
            } catch (IOException | MyException e) {
                System.out.println("\u001B[31m" + e.getMessage() + "\u001B[0m");
            }
        });
        repo.setPrgList(programStates);
    }

    public void allStep() throws MyException, IOException, InterruptedException {

        executorService = Executors.newFixedThreadPool(2);
        List<PrgState> programStates = removeCompletedPrg(repo.getPrgList());

        while (programStates.size() > 0) {
            conservativeGarbageCollector(programStates);
            oneStepForAllPrg(programStates);
            programStates = removeCompletedPrg(repo.getPrgList());
        }
        executorService.shutdownNow();
        repo.setPrgList(programStates);
    }

    public void oneStep() throws MyException, InterruptedException {
        executorService = Executors.newFixedThreadPool(2);
        List<PrgState> programStates = removeCompletedPrg(repo.getPrgList());
        oneStepForAllPrg(programStates);
        conservativeGarbageCollector(programStates);
        //programStates = removeCompletedPrg(repository.getProgramList());
        executorService.shutdownNow();
        //repository.setProgramStates(programStates);
    }


    public Map<Integer, Value> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapAddr, Map<Integer, Value> heap) {
        return heap.entrySet().stream()
                .filter(e -> ( symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    List<Integer> getAddrFromSymTable(Collection<Value> symTableValues){
        return symTableValues.stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {
                    RefValue v1 = (RefValue)v; return v1.getAddr();})
                .collect(Collectors.toList());
    }
    public List<Integer> getAddrFromHeap(Collection<Value> heapValues) {
        return heapValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue) v; return v1.getAddr();})
                .collect(Collectors.toList());
    }

    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
        return inPrgList.stream().filter(p -> !p.isNotCompleted()).collect(Collectors.toList());
    }

    private void display(PrgState programState) {
        if (display_flag) {
            System.out.println(programState.toString());
        }
    }

    public void conservativeGarbageCollector(List<PrgState> programStates) {
        List<Integer> symTableAddresses = Objects.requireNonNull(programStates.stream()
                        .map(p -> getAddrFromSymTable(p.getSymTable().values()))
                        .map(Collection::stream)
                        .reduce(Stream::concat).orElse(null))
                .collect(Collectors.toList());
        programStates.forEach(p -> {
            p.getHeap().setContent((HashMap<Integer, Value>) safeGarbageCollector(symTableAddresses, getAddrFromHeap(p.getHeap().getContent().values()), p.getHeap().getContent()));
        });
    }
    public List<PrgState> getProgramStates() {
        return this.repo.getPrgList();
    }

    public void setProgramStates(List<PrgState> programStates) {
        this.repo.setPrgList(programStates);
    }
}
