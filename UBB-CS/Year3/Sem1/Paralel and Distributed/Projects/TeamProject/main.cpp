#include <iostream>
#include <vector>
#include <mpi.h>


void printChessboard(const std::vector<int>& queens) {///simple matrix print
    int n = queens.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (queens[i] == j) {
                std::cout << "Q ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool isValid(const std::vector<int>& queens, int row, int col) {///check function for valid queen pos
    for (int i = 0; i < row; ++i) {
        // Check if there is a queen in the same column or diagonals
        if (queens[i] == col || queens[i] - i == col - row || queens[i] + i == col + row) {
            return false;
        }
    }
    return true;
}

void solveNQueens(int n, int startRow, int endRow, int& localSolutions) {
    std::vector<int> queens(n, -1);
    std::vector<int> stack(n, 0);
    int row = startRow;

    while (row >= startRow && row < endRow) {
        if (stack[row] == n) {
            stack[row] = 0;
            --row;
            continue;
        }

        int col = stack[row];
        stack[row]++;

        if (isValid(queens, row, col)) {
            queens[row] = col;

            if (row == n - 1) {
                // Found a solution, increment the local solutions counter
                localSolutions++;
                // Print the chessboard for the current solution
                // printChessboard(queens);
            } else {
                row++;
            }
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, numProcesses;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    int n = 12; // Set the size of the chessboard

    int localSolutions = 0;
    std::vector<int> solutions(numProcesses, 0);

    double startTime = MPI_Wtime();

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate the number of rows each worker should handle
    int rowsPerWorker = n / numProcesses;
    int extraRows = n % numProcesses;

    // Determine the start and end rows for this process
    int startRow = rank * rowsPerWorker + std::min(rank, extraRows);
    int endRow = startRow + rowsPerWorker + (rank < extraRows ? 1 : 0);

    solveNQueens(n, startRow, endRow, localSolutions);

    // Gather local solutions from all processes to process 0
    MPI_Gather(&localSolutions, 1, MPI_INT, &solutions[0], 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Process 0 prints the total number of solutions and time
    if (rank == 0) {
        int totalSolutions = 0;
        for (int i = 0; i < numProcesses; ++i) {
            totalSolutions += solutions[i];
        }
        std::cout << "Total solutions: " << totalSolutions << "\n";
        double endTime = MPI_Wtime();
        std::cout << "Total Time: " << endTime - startTime << " seconds\n";
    }

    MPI_Finalize();
    return 0;
}