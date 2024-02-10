//
// Created by Dragos on 1/4/2024.
//
#include "dsm.h"

DSM::DSM(int numProcesses, int numVariables)
        : numProcesses(numProcesses), numVariables(numVariables),
          variables(numProcesses, std::vector<int>(numVariables, 0)),
          callbacks(numProcesses, std::vector<std::vector<std::function<void(int, int)>>>(numVariables)) {}

void DSM::write(int processId, int variableId, int value) {
    std::lock_guard<std::mutex> lock(mutex);

    variables[processId][variableId] = value;

    ///check and initialize callbacks if needed
    if (callbacks[processId][variableId].empty()) {
        callbacks[processId][variableId].emplace_back([](int, int) {});
    }

    ///notify subscribers about the change
    for (auto& callback : callbacks[processId][variableId]) {
        callback(processId, variableId);
    }
}

void DSM::subscribe(int processId, int variableId, std::function<void(int, int)> callback) {
    std::lock_guard<std::mutex> lock(mutex);
    callbacks[processId][variableId].push_back(callback);
}

bool DSM::compareAndExchange(int processId, int variableId, int expectedValue, int newValue) {
    std::lock_guard<std::mutex> lock(mutex);

    if (variables[processId][variableId] == expectedValue) {
        variables[processId][variableId] = newValue;
        return true;
    }
    return false;
}

int DSM::readValue(int processId, int variableId) const {
    return variables[processId][variableId];
}