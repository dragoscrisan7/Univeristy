#include <stdio.h>

int prime(int n)
{
    int ok = 0;
    while(ok != 1)
    {
        n += 2;
        ok = 1;
        for(int d = 3;d <= n/2; d=d+2)
            if(n % d == 0)
                ok = 0;
    }
    return n;
}

int gcd(int a, int b) {
    if (a > b) {
        gcd(a - b, b);
    }
    else if (a < b) {
        gcd(a, b - a);
    }
    else {
        return a;
    }
}
void read(int v[], int *len)
{
    int x;
    scanf_s("%d", &x);
    while(x != 0) {
        v[*len] = x;
        *len = *len + 1;
        scanf_s("%d", &x);
    }
}

void array(int v[], int len, int *startx, int *maxx)
{
    int start = 0, end = 0;
    while(len > 1){
        if (gcd(v[end], v[end + 1]) != 1) {
            if (*maxx < end - start + 1) {
                *startx = start;
                *maxx = end - start + 1;
            }
            start = end + 1;
        }
        end++;
        len--;
    }
    if (*maxx < end - start + 1) {
        *startx = start;
        *maxx = end - start + 1;
    }
}

void primes_smaller_than_n(int n)
{
    int x;
    if(n>2){
        printf("2");
        x = 3;
        while(x<n){
            printf(", %d", x);
            x = prime(x);
        }
        printf("\n");
    }
}

int main()
{
    int p, loop = 1;
    while(loop == 1) {
        printf("1.Type 1 to generate the first n prime numbers\n2.Type 2 to find the longest subsequence with any"
               "2 consecutive numbers relatively prime\n3.Type 3 to generate all the prime numbers smaller than the "
               "given number\n4.Type 4 to exit\n");
        scanf_s("%d", &p);
        if (p == 1) {
            int n;
            printf_s("n= ");
            scanf_s("%d", &n);
            if (n >= 1) {
                printf("2");
                n--;
                int m = 1;
                while (n != 0) {
                    m = prime(m);
                    printf(", %d", m);
                    n--;
                }
                printf("\n");
            }
        } else if (p == 2) {
            int v[4000], len = 0, maxx = 0, startx;
            read(v,&len);
            array(v,len, &startx, &maxx);

            for(int d = 0; d<maxx; d++){
                printf("%d ", v[startx]);
                startx++;
            }
            printf("\n");
        }else if (p == 4) {
            loop = 0;
        }else if (p==3){
            int n;
            scanf_s("%d", &n);
            primes_smaller_than_n(n);
        }
    }
    return 0;
}

