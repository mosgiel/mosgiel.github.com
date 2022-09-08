#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define WIDTH 746911

///Variable Declaration
int factorLimit = 100000;
int valueLimit = 1753089;
bool domain[WIDTH] = {[0 ... WIDTH - 1] = true};
int cycle;
int offset = -1;
int s = 0;

int detectCycleOffset(int x) {
    int m = 1;
    for (int i = 0; i <= x; ++i) {
        m = (3 * m) % x;
        if (m + 2 == x) {
            offset = i + 1;
        }
        if (m == 1) {
            cycle = i + 1;
            return 0;
        }
    }
}

void updateDomain() {
    if (offset != -1) {
        int d = 0;
        for (int i = 0; i < cycle; ++i) {
            if ((valueLimit + i) % cycle == offset) {
                d = i;
            }
        }
        while (d < WIDTH) {
            if (domain[d] == true) {
                ++s;
            }
            domain[d] = false;
            d += cycle;
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
    time_t t1;
    t1 = time(NULL);

    FILE *fp;
    fp = fopen("results.txt", "w");

    ///Sieve Mechanics
    int i = 0;
    int k = 5;
    while (i < factorLimit) {
        if (checkPrime(k) == true) {
            detectCycleOffset(k);
            updateDomain();
        }
        cycle = 0;
        offset = -1;
        k += 2;
        ++i;
        if (i % (factorLimit / 100) == 0) {
            time_t t2;
            t2 = time(NULL);
            printf("\rAmount Sieved: %d, Candidates Removed: %d, Time: %d", i, s, t2 - t1);
        }
    }
    printf("\r");
    for (int i = 0; i < WIDTH; ++i) {
        if (domain[i] == true) {
            printf("%d ", i + valueLimit);
            fprintf(fp, "," + i + valueLimit);
        }
    }
    return 0;
}
