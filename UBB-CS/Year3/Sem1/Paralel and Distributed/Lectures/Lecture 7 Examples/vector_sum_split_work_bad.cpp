/* This program computes the sum of two vectors into a third one, using a configured number of threads.
* It shows how to NOT split the work evenly between working threads because of the caching effects - each thread takes every k-th element
* (where k is the number of threads), resulting in more cache misses and false sharing problems.
*/

#include <stdio.h>
#include <stdint.h>
#include <memory>
#include <thread>
#include <vector>
#include <chrono>

/* Does the work for a single thread from computing the pointwise sum of 'a' to 'b' into 'c'*/
void sumForOneThread(int const* a, int const* b, int* c, size_t totalSize, size_t idxThread, size_t nrThreads)
{
    for (size_t i = idxThread; i < totalSize; i += nrThreads)
    {
        c[i] = a[i] + b[i];
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
    c.reset(new int[nrElements]);


    std::vector<std::thread> threads;
    threads.reserve(nrThreads);
    std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < nrThreads; ++i) {
        threads.emplace_back(sumForOneThread, a.get(), b.get(), c.get(), nrElements, i, nrThreads);
    }
    for (int i = 0; i < nrThreads; ++i) {
        threads[i].join();
    }
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    printf("Used time = %lldus\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - beginTime).count());
}