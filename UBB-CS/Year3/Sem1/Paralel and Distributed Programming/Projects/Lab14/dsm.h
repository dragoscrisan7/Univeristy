//
// Created by Dragos on 1/4/2024.
//

#ifndef LAB14_DSM_H
#define LAB14_DSM_H

#include <iostream>
#include <vector>
#include <functional>
#include <mutex>

class DSM {
public:
    DSM(int numProcesses, int numVariables);

    void write(int processId, int variableId, int value);

    void subscribe(int processId, int variableId, std::function<void(int, int)> callback);

    bool compareAndExchange(int processId, int variableId, int expectedValue, int newValue);

    int readValue(int processId, int variableId) const;

private:
    int numProcesses;
    int numVariables;
    std::vector<std::vector<int>> variables; // Matrix representing variables for each process
    std::vector<std::vector<std::vector<std::function<void(int, int)>>>> callbacks; // Matrix of callbacks
    std::mutex mutex; // Mutex for thread safety
};

#endif //LAB14_DSM_H
