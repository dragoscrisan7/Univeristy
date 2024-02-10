#ifndef LAB6_MULTITHREADS_H
#define LAB6_MULTITHREADS_H

#include "../utils/Utils.h"

void MTparallelMatrixProduct(const std::vector<std::vector<int>>& matrixA, const std::vector<std::vector<int>>& matrixB, std::vector<std::vector<int>>& result, int taskID, int numTasks);


#endif //LAB6_MULTITHREADS_H