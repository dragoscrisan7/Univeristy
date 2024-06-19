#include <iostream>
#include <vector>
#include <mpi.h>
#include <chrono>

using namespace std;

void printPolynomial(const vector<int>& poly) {///simple print function
    for (int i = 0; i < poly.size(); ++i) {
        cout << poly[i] << "x^" << i;
        if (i < poly.size() - 1) {
            cout << " + ";
        }
    }
    cout << endl;
}

vector<int> addPolynomials(const vector<int>& A, const vector<int>& B) {///simple add function
    int size = max(A.size(), B.size());
    vector<int> result(size, 0);

    for (int i = 0; i < A.size(); ++i) {
        result[i] += A[i];
    }

    for (int i = 0; i < B.size(); ++i) {
        result[i] += B[i];
    }

    return result;
}

vector<int> subtractPolynomials(const vector<int>& A, const vector<int>& B) {///simple substract function
    int size = max(A.size(), B.size());
    vector<int> result(size, 0);

    for (int i = 0; i < A.size(); ++i) {
        result[i] += A[i];
    }

    for (int i = 0; i < B.size(); ++i) {
        result[i] -= B[i];
    }

    return result;
}

vector<int> multiplyPolynomialsKaratsuba(const vector<int>& A, const vector<int>& B) {
    int n = max(A.size(), B.size());

    if (n <= 4) {
        vector<int> result(n * 2 - 1, 0);
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < B.size(); ++j) {
                result[i + j] += A[i] * B[j];
            }
        }
        return result;
    }

    int m = (n + 1) / 2;

    vector<int> A1(A.begin(), A.begin() + m);
    vector<int> A2(A.begin() + m, A.end());

    vector<int> B1(B.begin(), B.begin() + m);
    vector<int> B2(B.begin() + m, B.end());

    vector<int> P1 = multiplyPolynomialsKaratsuba(A1, B1);
    vector<int> P2 = multiplyPolynomialsKaratsuba(A2, B2);

    vector<int> A1_A2 = addPolynomials(A1, A2);
    vector<int> B1_B2 = addPolynomials(B1, B2);

    vector<int> P3 = multiplyPolynomialsKaratsuba(A1_A2, B1_B2);
    P3 = subtractPolynomials(P3, P1);
    P3 = subtractPolynomials(P3, P2);

    vector<int> result(2 * n - 1, 0);

    for (int i = 0; i < P1.size(); ++i) {
        result[i] += P1[i];
    }

    for (int i = 0; i < P2.size(); ++i) {
        result[i + 2 * m] += P2[i];
    }

    for (int i = 0; i < P3.size(); ++i) {
        result[i + m] += P3[i];
    }

    return result;
}

vector<int> multiplyPolynomialsRegular(const vector<int>& A, const vector<int>& B) {
    int n = A.size();
    int m = B.size();
    vector<int> result(n + m - 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result[i + j] += A[i] * B[j];
        }
    }

    return result;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    vector<int> A = {1, 2, 3};  /// Example polynomial: 1 + 2x + 3x^2
    vector<int> B = {4, 5};     /// Example polynomial: 4 + 5x

    int localSizeA = A.size() / size;
    int localSizeB = B.size() / size;

    vector<int> localA(localSizeA, 0);
    vector<int> localB(localSizeB, 0);

    MPI_Scatter(A.data(), localSizeA, MPI_INT, localA.data(), localSizeA, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B.data(), localSizeB, MPI_INT, localB.data(), localSizeB, MPI_INT, 0, MPI_COMM_WORLD);

    auto startRegular = std::chrono::high_resolution_clock::now();
    vector<int> resultRegular = multiplyPolynomialsRegular(localA, localB);
    auto stopRegular = std::chrono::high_resolution_clock::now();
    auto durationRegular = std::chrono::duration_cast<std::chrono::microseconds>(stopRegular - startRegular);

    auto startKaratsuba = std::chrono::high_resolution_clock::now();
    vector<int> localResultKaratsuba = multiplyPolynomialsKaratsuba(localA, localB);
    auto stopKaratsuba = std::chrono::high_resolution_clock::now();
    auto durationKaratsuba = std::chrono::duration_cast<std::chrono::microseconds>(stopKaratsuba - startKaratsuba);


    vector<int> resultKaratsuba(A.size() + B.size() - 1, 0);
    MPI_Gather(localResultKaratsuba.data(), localResultKaratsuba.size(), MPI_INT, resultKaratsuba.data(), localResultKaratsuba.size(), MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {///0 to check if process is root
        cout << "Polynomial A: ";
        printPolynomial(A);

        cout << "Polynomial B: ";
        printPolynomial(B);

        cout << "Regular Polynomial Multiplication Result: ";
        printPolynomial(resultRegular);
        cout << "Time taken for regular multiplication: " << durationRegular.count() << " microseconds\n";

        cout << "Karatsuba Polynomial Multiplication Result: ";
        printPolynomial(resultKaratsuba);
        cout << "Time taken for Karatsuba multiplication: " << durationKaratsuba.count() << " microseconds\n";
    }

    MPI_Finalize();

    return 0;
}
