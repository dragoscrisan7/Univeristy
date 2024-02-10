#include "MultiThreads.h"

void MTparallelMatrixProduct(const std::vector<std::vector<int>>& matrixA, const std::vector<std::vector<int>>& matrixB, std::vector<std::vector<int>>& result, int taskID, int numTasks) {
    int numRows = matrixA.size();
    int numCols = matrixB[0].size();

    for (int row = taskID; row < numRows; row += numTasks) {
        for (int col = 0; col < numCols; col++) {
            result[row][col] = computeElement(matrixA, matrixB, row, col);
        }
    }
}