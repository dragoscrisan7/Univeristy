#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <minmax.h>

int gcd1(int a, int b) {
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    // Get the greatest power of 2 that divides both a and b
    int commonPowerOfTwo = 0;
    while ((a & 1) == 0 && (b & 1) == 0) {
        a >>= 1;
        b >>= 1;
        commonPowerOfTwo++;
    }

    while (a != b) {
        while ((a & 1) == 0)
            a >>= 1;
        while ((b & 1) == 0)
            b >>= 1;
        if (a > b)
            a = (a - b) >> 1;
        else
            b = (b - a) >> 1;
    }

    // Multiply the result by 2^commonPowerOfTwo to get the final GCD
    return a << commonPowerOfTwo;
}

int gcd2(int a, int b)
{
    // Everything divides 0 (recursive stop conditions)
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    // base case
    if (a == b)
        return a;

    // we subtract the smaller number from the bigger number untill
    // we get the result(a=b)
    if (a > b)
        return gcd2(a - b, b);
    return gcd2(a, b - a);
}

int gcd3(int a, int b) {
    // base cases
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) return a;

    if (a % 2 == 0) {
        if (b % 2 == 0) // a is even, b is even (2)
            return 2 * gcd3(a / 2, b / 2);
        else            // a is even, b is odd (3)
            return gcd3(a / 2, b);
    } else {
        if (b % 2 == 0) // a is odd, b is even (3)
            return gcd3(a, b / 2);
        else            // a is odd, b is odd (4)
            return gcd3(abs(a - b), min(a, b));
    }
}

int average_time(int a, int b, int (*func)(int, int))
{
    int total_time = 0, gcd_result;
    for (int i = 0; i < 10; i++) {
        clock_t start = clock();
        gcd_result = gcd2(a, b);
        clock_t stop = clock();
        total_time += (stop - start)/ CLOCKS_PER_SEC;
    }
    printf("GCD of %d and %d is %d ", a, b, gcd_result);
    return (double)total_time;
}

// Driver program to test above function
int main()
{
    int a=943;
    int b=6583;
    printf("2: %d, 3: %d",gcd2(a,b),gcd3(a,b));
//    int pairs[10][2] = {
//            {2147483642, 982451652},
//            {123, 456},
//            {789, 1011},
//            {555, 333},
//            {777, 999},
//            {111, 222},
//            {98575, 123},
//            {9999, 1111},
//            {54321, 12345},
//            {987654, 123456}
//    };
//    for (int i = 0; i < 10; i++) {
//        int a = pairs[i][0];
//        int b = pairs[i][1];
//        printf("%d, %d\n",a,b);
//
//        double average_time_result = average_time(a, b, gcd1);
//        printf("Average Time elapsed for gcd1 over %d runs: %.5f seconds\n", 100, average_time_result);
//
//        double average_time_result2 = average_time(a, b, gcd2);
//        printf("Average Time elapsed for gcd2 over %d runs: %.5f seconds\n", 100, average_time_result2);
//
//        double average_time_result3 = average_time(a, b, gcd3);
//        printf("Average Time elapsed for gcd3 over %d runs: %.5f seconds\n", 100, average_time_result3);
//    }

    return 0;
}
