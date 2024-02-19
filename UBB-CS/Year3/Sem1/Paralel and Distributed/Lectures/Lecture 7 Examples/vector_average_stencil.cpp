/* This program computes the sum of two vectors into a third one, using a configured number of threads.
* It takes a vector and computes a second one where each element is the average of the 5 elements of the first one around that position.
*/

#include <stdio.h>
#include <stdint.h>
#include <memory>
#include <thread>
#include <vector>
#include <chrono>

/* Does the work for a single thread*/
void sumForOneThread(int const* a, int* b, size_t totalSize, size_t idxThread, size_t nrThreads)
{
    size_t beginIndex = (idxThread * totalSize) / nrThreads;
    size_t endIndex = ((idxThread + 1) * totalSize) / nrThreads;
    for (size_t i = beginIndex; i < endIndex; ++i)
    {
        int sum = 0;
        for (int j = -2; j <= 2; ++j)
        {
            if(int(i) + j >= 0 && int(i) + j < totalSize)
            {
                sum += a[i + j];
            }
        }
        b[i] = sum / 5;
    }
}

int main(int argc, char** argv)
{
    std::unique_ptr<int[]> a, b, c;
    long long nrElements;
    long long nrThreads;
    if (argc != 3 || 1 != sscanf(argv[1], "%lld", &nrElements)
        || 1 != sscanf(argv[2], "%lld", &nrThreads)) {
        fprintf(stderr, "Usage: vector_sum_split_work nrElements nrThreads\n");
        return 1;
    }
    a.reset(new int[nrElements]);
    b.reset(new int[nrElements]);


    std::vector<std::thread> threads;
    threads.reserve(nrThreads);
    std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < nrThreads; ++i) {
        threads.emplace_back(sumForOneThread, a.get(), b.get(), nrElements, i, nrThreads);
    }
    for (int i = 0; i < nrThreads; ++i) {
        threads[i].join();
    }
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    printf("Used time = %lldus\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - beginTime).count());
}