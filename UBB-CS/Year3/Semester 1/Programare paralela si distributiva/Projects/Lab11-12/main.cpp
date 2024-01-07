#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_set>

using namespace std;

const int V = 5;

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

void hamiltonianCycleParallel(int pos, const vector<vector<int>>& graph, vector<int>& path, unordered_set<string>& solutions, mutex& mtx) {
    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] == 1) {
            // Found a Hamiltonian cycle
            string solution;
            for (int i : path)
                solution += to_string(i) + " ";
            solution += to_string(path[0]);

            lock_guard<mutex> lock(mtx);
            if (solutions.find(solution) == solutions.end()) {
                printCycle(path);
                solutions.insert(solution);
            }
        }
        return;
    }

    vector<thread> threads;

    for (int v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            // Recur to construct the rest of the path
            threads.emplace_back(hamiltonianCycleParallel, pos + 1, cref(graph), ref(path), ref(solutions), ref(mtx));
        }
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }
}

void findHamiltonianCycleParallel(const vector<vector<int>>& graph) {
    vector<int> path(V, -1);
    path[0] = 0; // Start from vertex 0

    unordered_set<string> solutions;
    mutex mtx;

    // Start the parallel search
    hamiltonianCycleParallel(1, graph, path, solutions, mtx);
}

int main() {
    // Example graph represented as an adjacency matrix
    vector<vector<int>> graph = {
            {0, 1, 1, 1, 0},
            {1, 0, 1, 0, 1},
            {1, 1, 0, 1, 1},
            {1, 0, 1, 0, 1},
            {0, 1, 1, 1, 0}
    };

    // Find and print Hamiltonian cycle in parallel
    findHamiltonianCycleParallel(graph);

    return 0;
}
