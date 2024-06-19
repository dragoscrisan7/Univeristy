#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_set>

using namespace std;

bool isSafe(int v, const vector<vector<int>>& graph, vector<int>& path, int pos) {
    if (graph[path[pos - 1]][v] == 0)
        return false;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

void printCycle(const vector<int>& path) {
    cout << "Hamiltonian Cycle: ";
    for (int i : path)
        cout << i << " ";
    cout << path[0] << endl;
}

void hamiltonianCycleParallel(int pos, const vector<vector<int>>& graph, vector<int> path, unordered_set<string>& solutions, mutex& mtx) {
    const int V = graph.size();

    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] == 1) {///found a Hamiltonian cycle
            string solution;
            for (int i : path)
                solution += to_string(i) + " ";
            solution += to_string(path[0]);

            unique_lock<mutex> lock(mtx);
            if (solutions.find(solution) == solutions.end()) {
                printCycle(path);
                solutions.insert(solution);
            }
            lock.unlock();
        }
        return;
    }

    vector<thread> threads;

    for (int v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            /// recur to construct the rest of the path
            threads.emplace_back(hamiltonianCycleParallel, pos + 1, cref(graph), ref(path), ref(solutions), ref(mtx));
        }
    }

    /// wait for threads to finish
    for (auto& t : threads) {
        t.join();
    }
}

void findHamiltonianCycleParallel(const vector<vector<int>>& graph) {
    vector<int> path(graph.size(), -1);
    path[0] = 0; ///start from 0

    unordered_set<string> solutions;///no repeating solutions
    mutex mtx;

    ///start the parallel search
    hamiltonianCycleParallel(1, graph, path, solutions, mtx);
}

int main() {
    vector<vector<int>> graph1 = {
            {0, 1, 1, 1, 0},
            {1, 0, 1, 0, 1},
            {1, 1, 0, 1, 1},
            {1, 0, 1, 0, 1},
            {0, 1, 1, 1, 0}
    };
    vector<vector<int>> graph2 = {
            {0, 1, 1, 1, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 0},
            {1, 1, 0, 1, 1, 0, 0},
            {1, 0, 1, 0, 1, 0, 0},
            {0, 1, 1, 1, 0, 1, 1},
            {0, 0, 0, 0, 1, 0, 1},
            {0, 0, 0, 0, 1, 1, 0}
    };

    vector<vector<int>> graph3 = {
            {0, 1, 1, 1, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 0},
            {1, 1, 0, 1, 1, 0, 0},
            {1, 0, 1, 0, 1, 0, 0},
            {0, 1, 1, 1, 0, 1, 0},
            {0, 0, 0, 0, 1, 0, 1},
            {0, 0, 0, 0, 0, 1, 0}
    };

    vector<vector<int>> graph4 = {
            {0, 1, 0, 1, 0},
            {1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0},
            {1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0}
    };


    findHamiltonianCycleParallel(graph1);

    return 0;
}
