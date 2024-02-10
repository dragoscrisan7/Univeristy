// main.cpp
#include <iostream>
#include "dsm.h"

int main() {
    const int numProcesses = 3;
    const int numVariables = 2;

    DSM dsm(numProcesses, numVariables);

    dsm.write(2, 0, 99);

    // Subscribe to variable changes
    for (int processId = 0; processId < numProcesses; ++processId) {
        for (int variableId = 0; variableId < numVariables; ++variableId) {
            dsm.subscribe(processId, variableId, [](int processId, int variableId) {
                std::cout << "Process " << processId << " saw a change in variable " << variableId << std::endl;
            });
        }
    }

    // Test write and compareAndExchange operations
    dsm.write(0, 0, 42);
    dsm.write(1, 1, 10);

    std::cout << "Value at (1, 1): " << dsm.readValue(1, 1) << std::endl;

    bool success = dsm.compareAndExchange(1, 1, 10, 99);
    std::cout << "Compare and Exchange Result: " << (success ? "Success" : "Failure") << std::endl;
    std::cout << "New Value at (1, 1): " << dsm.readValue(1, 1) << std::endl;

    return 0;
}
