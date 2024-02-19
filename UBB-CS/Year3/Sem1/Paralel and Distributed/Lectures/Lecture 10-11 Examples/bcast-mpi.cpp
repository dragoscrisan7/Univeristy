#include <iostream>
#include <sstream>
#include <mpi.h>
#include <vector>

void printVector(std::vector<int> const& values, int me)
{
    std::stringstream ss;
    ss << "Me : " << me << ", values:";
    for(int v : values) ss << " " << v;
    std::cout << ss.str() << "\n";
}

int main()
{
    MPI_Init(0, 0);
    int me;
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    std::cout << "Hello, I am " << me << " out of " << size << "\n";

    std::vector<int> values;
    size_t const n = 25;
    if(me == 0) {
        values.reserve(n);
        for(size_t i=0 ; i<n ; ++i) values.push_back(i*i);
    } else {
        values.resize(n);
    }
    
    MPI_Bcast(values.data(), values.size(), MPI_INT, 0, MPI_COMM_WORLD);
    
    printVector(values, me);
    
    
    MPI_Finalize();
}