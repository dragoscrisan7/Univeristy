//
// Created by Dragos on 1/4/2024.
//
#include "dsm.h"

DSM::DSM(int numProcesses, int numVariables)
        : numProcesses(numProcesses), numVariables(numVariables),
          variables(numProcesses, std::vector<int>(numVariables, 0)),
          callbacks(numProcesses, std::vector<std::vector<std::function<void(int, int)>>>()) {}

void DSM::write(int processId, int variableId, int value) {
    variables[processId][variableId] = value;

    // Notify subscribers about the change
    for (auto& callback : callbacks[processId][variableId]) {
        callback(processId, variableId);
    }
}

void DSM::subscribe(int processId, int variableId, std::function<void(int, int)> callback) {
    callbacks[processId][variableId].push_back(callback);
}

bool DSM::compareAndExchange(int processId, int variableId, int expectedValue, int newValue) {
    if (variables[processId][variableId] == expectedValue) {
        variables[processId][variableId] = newValue;
        return true;
    }
    return false;
}