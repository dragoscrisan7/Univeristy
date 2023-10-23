//
// Created by Dragos on 10/24/2023.
//

#ifndef LAB6_UTILS_H
#define LAB6_UTILS_H

#include <iostream>
#include <vector>
#include <random>

std::vector<std::vector<int>> generateRandomMatrix(int numRows, int numCols);
void printMatrix(const std::vector<std::vector<int>>& matrix);
int computeElement(const std::vector<std::vector<int>>& matrixA, const std::vector<std::vector<int>>& matrixB, int row, int col);


#endif //LAB6_UTILS_H