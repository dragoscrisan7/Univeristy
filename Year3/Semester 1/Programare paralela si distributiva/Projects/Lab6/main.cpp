#include <iostream>
#include <vector>
#include <thread>
#include "utils/Utils.h"

#include "threadsPool/ThreadPool.h"
#include "multiThreads/MultiThreads.h"

int main() {
    int numRowsA = 3;
    int numColsA = 3;
    int numRowsB = 3;
    int numColsB = 3;

    // Generate random matrices
    std::vector<std::vector<int>> matrixA = generateRandomMatrix(numRowsA, numColsA);
    std::vector<std::vector<int>> matrixB = generateRandomMatrix(numRowsB, numColsB);

    int numTasks = 4;
    std::vector<std::vector<int>> result(numRowsA, std::vector<int>(numColsB, 0));

///--------------------------------------------------------------------------------------------------------------

//    std::vector<std::thread> threads;
//
//    for (int i = 0; i < numTasks; i++) {
//        threads.push_back(std::thread(MTparallelMatrixProduct, std::ref(matrixA), std::ref(matrixB), std::ref(result), i, numTasks));
//    }
//
//    for (int i = 0; i < numTasks; i++) {
//        threads[i].join();
//    }

///--------------------------------------------------------------------------------------------------------------

    ThreadPool pool(numTasks);

    for (int i = 0; i < numTasks; i++) {
        pool.enqueue([i, &matrixA, &matrixB, &result, numTasks]() {
            TPparallelMatrixProduct(matrixA, matrixB, result, i, numTasks);
        }); // Debugging output
    }

    pool.close();

///--------------------------------------------------------------------------------------------------------------

    std::cout << "Matrix A:" << std::endl;
    printMatrix(matrixA);

    std::cout << "Matrix B:" << std::endl;
    printMatrix(matrixB);

    std::cout << "Resulting Matrix:" << std::endl;
    printMatrix(result);

    return 0;
}