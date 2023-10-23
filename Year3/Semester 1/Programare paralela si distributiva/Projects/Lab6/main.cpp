#include <iostream>
#include <vector>
#include <thread>
#include "utils/Utils.h"

#include "threadsPool/ThreadPool.h"
#include "multiThreads/MultiThreads.h"

int main() {
    int numRowsA = 9;
    int numColsA = 9;
    int numRowsB = 9;
    int numColsB = 9;

    // Generate random matrices
    std::vector<std::vector<int>> matrixA = generateRandomMatrix(numRowsA, numColsA);
    std::vector<std::vector<int>> matrixB = generateRandomMatrix(numRowsB, numColsB);

    int numTasks = 4;
    int numRows = matrixA.size();
    int numCols = matrixB[0].size();

///--------------------------------------------------------------------------------------------------------------

    std::vector<std::thread> threads;
    std::vector<std::vector<int>> result(numRows, std::vector<int>(numCols, 0));

    for (int i = 0; i < numTasks; i++) {
        threads.push_back(std::thread(MTparallelMatrixProduct, std::ref(matrixA), std::ref(matrixB), std::ref(result), i, numTasks));
    }

    for (int i = 0; i < numTasks; i++) {
        threads[i].join();
    }

///--------------------------------------------------------------------------------------------------------------

//    ThreadPool pool(numTasks);
//
//    std::vector<std::vector<int>> result(numRows, std::vector<int>(numCols, 0));
//
//    for (int i = 0; i < numTasks; i++) {
//        pool.enqueue(TPparallelMatrixProduct, matrixA, matrixB, std::ref(result), i, numTasks);
//    }
//
//    pool.wait();

///--------------------------------------------------------------------------------------------------------------

    std::cout << "Matrix A:" << std::endl;
    printMatrix(matrixA);

    std::cout << "Matrix B:" << std::endl;
    printMatrix(matrixB);

    std::cout << "Resulting Matrix:" << std::endl;
    printMatrix(result);

    return 0;
}