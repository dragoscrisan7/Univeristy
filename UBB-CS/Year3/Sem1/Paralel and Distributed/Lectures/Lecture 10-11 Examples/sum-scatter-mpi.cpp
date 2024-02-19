/* A distributed program, using MPI, that sums up the elements in a vector of integers.
  - The main process splits the vector into equal size chunks and distributes them to all processes (including to itself),
  - each process sums the numbers in its chunk and sends the sum back to the main process
  - the main process gets the sums of the chunks, sums them and prints the result

This example uses MPI_scatter() to split the vector and send the chunks to the workers.
*/

#include <iostream>
#include <mpi.h>
#include <vector>
#include <time.h>
#include <chrono>
#include <stdint.h>

using namespace std;

// generates a random vector, to be used as input
void generate(vector<int>& v, size_t n)
{
    v.reserve(n);
    for(size_t i=0 ; i<n ; ++i) {
        // v.push_back(rand());
        v.push_back((i*101011) % 123456);
    }
}

// computes and checks the sum, to prove that the program is correct
inline bool checkSum(const vector <int> &v, int sum) {
    int _sum = 0;
    for(auto it : v) {
        _sum += it;
    }
    return _sum == sum;
}

// The actual work, to be executed both by the master and the workers. The input vector v and the value nrProcs are ignored on workers.
int process(vector<int> const& v, int me, int nrProcs)
{
    int chunkSize = v.size()/nrProcs;
    MPI_Bcast(&chunkSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    vector<int> chunk(chunkSize, 0);
    MPI_Scatter(v.data(), chunkSize, MPI_INT,
        chunk.data(), chunk.size(), MPI_INT,
        0, MPI_COMM_WORLD);
    cerr<<"Process "<<me<<" has chunk size="<<chunkSize<<"\n";
    int s = 0;
    for(auto v : chunk) {
        s += v;
    }
    vector<int> sums;
    if(me == 0) {
        sums.resize(nrProcs);
    }
    MPI_Gather(&s, 1, MPI_INT,
        sums.data(), 1, MPI_INT,
        0, MPI_COMM_WORLD);
    if(me == 0) {
        s = 0;
        for(auto v : sums) {
            s+=v;
        }
        return s;
    } else {
        return 0;
    }
}

int vectorSum(vector<int> v, int nrProcs) {
    v.resize(((v.size()+nrProcs-1)/nrProcs)*nrProcs, 0);
    return process(v, 0, nrProcs);
}

int main(int argc, char** argv)
{
    MPI_Init(0, 0);
    int me;
    int nrProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &nrProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    unsigned n;
    vector<int> v;
    if(argc != 2 || 1!=sscanf(argv[1], "%u", &n) ){
        fprintf(stderr, "usage: sum-mpi <n>\n");
        return 1;
    }

    if(me == 0) {
        generate(v, n);
        fprintf(stderr, "generated\n");
        chrono::high_resolution_clock::time_point const beginTime = chrono::high_resolution_clock::now();
        
        int sum = vectorSum(v, nrProcs);
        chrono::high_resolution_clock::time_point const endTime = chrono::high_resolution_clock::now();
        
        printf("Result %s, time=%ldms\n", (checkSum(v, sum) ? "ok" : "FAIL"),
            (chrono::duration_cast<chrono::milliseconds>(endTime-beginTime)).count());
    } else {
        // worker
        chrono::high_resolution_clock::time_point const beginTime = chrono::high_resolution_clock::now();
        process(vector<int>(), me, nrProcs);
        chrono::high_resolution_clock::time_point const endTime = chrono::high_resolution_clock::now();
        
        printf("(worker %d): time=%ldms\n", me, 
            (chrono::duration_cast<chrono::milliseconds>(endTime-beginTime)).count());
    }
    MPI_Finalize();
}