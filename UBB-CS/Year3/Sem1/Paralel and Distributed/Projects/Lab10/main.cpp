#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

void printPoly(const vector<int>& poly) {
    for (int i = 0; i < poly.size(); ++i) {
        cout << poly[i] << "x^" << i;
        if (i < poly.size() - 1) {
            cout << " + ";
        }
    }
    cout << endl;
}

vector<int> multiplyPolynomials(const vector<int>& A, const vector<int>& B) {
    int size = A.size() + B.size() - 1;
    vector<int> result(size, 0);

    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B.size(); ++j) {
            result[i + j] += A[i] * B[j];
        }
    }

    return result;
}

vector<int> parallelMultiplyPolynomials(const vector<int>& A, const vector<int>& B) {
    int size = A.size() + B.size() - 1;
    vector<int> result(size, 0);

    #pragma omp parallel for
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B.size(); ++j) {
            #pragma omp atomic
            result[i + j] += A[i] * B[j];
        }
    }

    return result;
}

vector<int> addPolynomials(const vector<int>& A, const vector<int>& B, bool subtract = false) {
    vector<int> result(A.size());
    for (int i = 0; i < A.size(); ++i) {
        result[i] = subtract ? A[i] - B[i] : A[i] + B[i];
    }
    return result;
}

vector<int> multiplyByPowerOfX(const vector<int>& A, int exp) {
    vector<int> result(A.size() + exp, 0);
    for (int i = 0; i < A.size(); ++i) {
        result[i + exp] = A[i];
    }
    return result;
}

vector<int> karatsuba(const vector<int>& A, const vector<int>& B) {
    int n = A.size();

    ///if the polynomials are small, use regular multiplication
    if (n <= 32) {
        vector<int> result(n * 2 - 1, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i + j] += A[i] * B[j];
            }
        }
        return result;
    }

    ///split the polynomials into two halves
    int mid = n / 2;
    vector<int> A1(A.begin(), A.begin() + mid);
    vector<int> A2(A.begin() + mid, A.end());
    vector<int> B1(B.begin(), B.begin() + mid);
    vector<int> B2(B.begin() + mid, B.end());

    ///recursive
    vector<int> P1 = karatsuba(A1, B1);
    vector<int> P2 = karatsuba(A2, B2);
    vector<int> P3 = karatsuba(addPolynomials(A1, A2), addPolynomials(B1, B2));

    ///combine results
    return addPolynomials(addPolynomials(multiplyByPowerOfX(P1, 2 * mid), P2), multiplyByPowerOfX(addPolynomials(addPolynomials(P3, P1, true), P2, true), mid));
}

vector<int> parallelKaratsuba(const vector<int>& A, const vector<int>& B) {
    int n = A.size();

    ///if the polynomials are small, use regular multiplication
    if (n <= 32) {
        vector<int> result(n * 2 - 1, 0);
        #pragma omp parallel for
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                #pragma omp atomic
                result[i + j] += A[i] * B[j];
            }
        }
        return result;
    }

    ////split the polynomials into two halves
    int mid = n / 2;
    vector<int> A1(A.begin(), A.begin() + mid);
    vector<int> A2(A.begin() + mid, A.end());
    vector<int> B1(B.begin(), B.begin() + mid);
    vector<int> B2(B.begin() + mid, B.end());

    ///recursive
    vector<int> P1, P2, P3;
    #pragma omp parallel sections
    {
        #pragma omp section
        P1 = parallelKaratsuba(A1, B1);

        #pragma omp section
        P2 = parallelKaratsuba(A2, B2);

        #pragma omp section
        P3 = parallelKaratsuba(addPolynomials(A1, A2), addPolynomials(B1, B2));
    }

    ///combine results
    return addPolynomials(addPolynomials(multiplyByPowerOfX(P1, 2 * mid), P2), multiplyByPowerOfX(addPolynomials(addPolynomials(P3, P1, true), P2, true), mid));
}

int main() {
//    vector<int> A = {1, 2, 3, 4, 5}; ///Polynomial: 1 + 2x + 3x^2 + 4x^3 + 5x^4
//    vector<int> B = {5, 4, 3, 2, 1}; ///Polynomial: 5 + 4x + 3x^2 + 2x^3 + 1x^4

//    vector<int> A(101, 1);  /// Polynomial of degree 100 with all coefficients set to 1
//    vector<int> B(101, 1);

    vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
    vector<int> B = {31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 6, 7, 7, 8, 9, 10};

    cout << "Polynomial A: ";
    printPoly(A);

    cout << "Polynomial B: ";
    printPoly(B);

    // Regular multiplication
    auto start = chrono::high_resolution_clock::now();
    vector<int> resultRegular = multiplyPolynomials(A, B);
    auto stop = chrono::high_resolution_clock::now();
    auto durationRegular = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << "Regular Multiplication Result: ";
    printPoly(resultRegular);

    cout << "Regular Multiplication Time: " << durationRegular.count() << " microseconds" << endl;

    // Parallelized Regular multiplication
    start = chrono::high_resolution_clock::now();
    vector<int> resultParallelRegular = parallelMultiplyPolynomials(A, B);
    stop = chrono::high_resolution_clock::now();
    auto durationParallelRegular = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << "Parallelized Regular Multiplication Result: ";
    printPoly(resultParallelRegular);

    cout << "Parallelized Regular Multiplication Time: " << durationParallelRegular.count() << " microseconds" << endl;

    // Karatsuba multiplication
    start = chrono::high_resolution_clock::now();
    vector<int> resultKaratsuba = karatsuba(A, B);
    stop = chrono::high_resolution_clock::now();
    auto durationKaratsuba = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << "Karatsuba Multiplication Result: ";
    printPoly(resultKaratsuba);

    cout << "Karatsuba Multiplication Time: " << durationKaratsuba.count() << " microseconds" << endl;

    // Parallelized Karatsuba multiplication
    start = chrono::high_resolution_clock::now();
    vector<int> resultParallelKaratsuba = parallelKaratsuba(A, B);
    stop = chrono::high_resolution_clock::now();
    auto durationParallelKaratsuba = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << "Parallelized Karatsuba Multiplication Result: ";
    printPoly(resultParallelKaratsuba);

    cout << "Parallelized Karatsuba Multiplication Time: " << durationParallelKaratsuba.count() << " microseconds" << endl;

    return 0;
}