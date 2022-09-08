#include <stdio.h>
#include <stdbool.h>
#include <math.h>

///Variable Declaration
int factorLimit = 1000;
int cycle;
int offset = -1;
int base = 3;
int konstant = 2;

int detectCycleOffset(int x) {
    int m = 1;
    for (int i = 0; i <= x; ++i) {
        m = (base * m) % x;
        if (m + konstant == x) {
            offset = i + 1;
        }
        if (m == 1) {
            cycle = i + 1;
            return 0;
        }
    }
}

bool checkPrime(int x) {

    float y = x;
    for (int i = 2; i <= sqrt(y); ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    ///Miscellaneous Management
    FILE *fp;
    fp = fopen("results.txt", "w");

    ///Sieve Mechanics
    int i = 0;
    int k = 5;
    while (i < factorLimit) {
        if (checkPrime(k) == true) {
            detectCycleOffset(k);
            printf("(%d, %d) ", cycle, offset);
            fprintf(fp, "(%d, %d) ", cycle, offset);
        }
        cycle = 0;
        offset = -1;
        k += 2;
        ++i;
    }
    return 0;
}

