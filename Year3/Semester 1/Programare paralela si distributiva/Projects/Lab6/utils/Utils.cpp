#include "Utils.h"

int computeElement(const std::vector<std::vector<int>>& matrixA, const std::vector<std::vector<int>>& matrixB, int row, int col) {
    int result = 0;
    for (int i = 0; i < matrixA[row].size(); ++i) {
        result += matrixA[row][i] * matrixB[i][col];
    }
    return result;
}

std::vector<std::vector<int>> generateRandomMatrix(int numRows, int numCols) {
    std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 0));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            matrix[i][j] = dist(gen);
        }
    }

    return matrix;
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}