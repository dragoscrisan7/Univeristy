#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

bool isPrimeMillerRabin(long long n, int k) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    // Find r and d such that n = 2^r * d + 1
    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    // Repeat the test 'k' times for accuracy
    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 4);
        long long x = modExp(a, d, n);

        if (x == 1 || x == n - 1) {
            continue;
        }

        for (long long r = 1; r < d; r *= 2) {
            x = modExp(x, 2, n);
            if (x == 1) return false;
            if (x == n - 1) break;
        }

        if (x != n - 1) return false;
    }

    return true;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator
    long long number = 17; // Change this to the number you want to test
    int iterations = 5; // Number of iterations

    if (isPrimeMillerRabin(number, iterations)) {
        std::cout << number << " is probably prime." << std::endl;
    } else {
        std::cout << number << " is composite." << std::endl;
    }

    return 0;
}