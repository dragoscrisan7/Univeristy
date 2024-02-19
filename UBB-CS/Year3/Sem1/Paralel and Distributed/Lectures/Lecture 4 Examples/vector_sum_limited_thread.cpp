#include <stdio.h>
#include <stdint.h>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>


std::unique_ptr<int[]> a, b;

void func(size_t start, size_t len, size_t iterations)
{
    for(size_t k=0 ; k<iterations ; ++k) {
        for(uint64_t i=0 ; i<len ; ++i) {
            a[start + i] = b[start + i] * b[start + i] * int(k);
        }
    }
}

int main(int argc, char** argv)
{
    long long nrThreads;
    long long lenPerThread;
    long long iterations;
    long long maxThreads;
    if(argc != 5 || 1!=sscanf(argv[1], "%lld", &nrThreads)
            || 1!=sscanf(argv[2], "%lld", &lenPerThread)
            || 1!=sscanf(argv[3], "%lld", &iterations)
            || 1!=sscanf(argv[4], "%lld", &maxThreads)){
        fprintf(stderr, "Usage: vector_sum_multithread nrThreads lenPerThread iterations maxThreads\n");
        return 1;
    }
    if (nrThreads < maxThreads) {
        maxThreads = nrThreads;
    }
    long long totalSize = nrThreads*lenPerThread;
    a.reset(new int[totalSize]);
    b.reset(new int[totalSize]);

    std::vector<std::thread> threads;
    threads.reserve(nrThreads);
    for(unsigned i=0 ; i<maxThreads ; ++i){
        threads.emplace_back(func, lenPerThread*i, lenPerThread, iterations);
    }
    for(unsigned i=maxThreads ; i<nrThreads ; ++i){
        threads[i-maxThreads].join();
        threads.emplace_back(func, lenPerThread*i, lenPerThread, iterations);
    }
    for(unsigned i=nrThreads-maxThreads ; i<nrThreads ; ++i){
        threads[i].join();
    }
}