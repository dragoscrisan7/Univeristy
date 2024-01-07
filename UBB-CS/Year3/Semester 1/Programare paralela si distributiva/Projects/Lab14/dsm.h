//
// Created by Dragos on 1/4/2024.
//

#ifndef LAB14_DSM_H
#define LAB14_DSM_H

#include <iostream>
#include <vector>
#include <functional>

class DSM {
public:
    DSM(int numProcesses, int numVariables);

    void write(int processId, int variableId, int value);

    void subscribe(int processId, int variableId, std::function<void(int, int)> callback);

    bool compareAndExchange(int processId, int variableId, int expectedValue, int newValue);

private:
    int numProcesses;
    int numVariables;
    std::vector<std::vector<int>> variables; // Matrix representing variables for each process
    std::vector<std::vector<std::vector<std::function<void(int, int)>>>> callbacks; // Matrix of callbacks
};

#endif //LAB14_DSM_H
