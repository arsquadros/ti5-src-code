#include <stdio.h>
#include <time.h>

#include "general.c"

#define CODE_ID 2

#define HARDWARE_ID -1 // edit to your id
#define SO -1 // edit to so's id

const int levels[] = {15LL, 20LL, 25LL};

unsigned long long iter_factorial(unsigned long long n) {
    if (n <= 1) return 1;
    else {
        unsigned long long res = 1;
        for (unsigned long long i = n; i > 1; i--) { res *= i; }
        return res;
    }
}

unsigned long long rec_factorial(unsigned long long n) {
    if (n == 1) return 1;
    else if (n > 1) {
        return n * rec_factorial(n-1);
    } else {
        return -1;
    }
}

unsigned long long factorial(unsigned long long n) {
    return rec_factorial(n);
}

int main() {
    FILE *fstream = fopen(FILEPATH, "w");

    register int n = 5000000;
    clock_t start, end;

    float *values = (float *)malloc(n * sizeof(float));
    start_results(fstream);

    for (register int level_calc = 0; level_calc < 3; level_calc++) {
        for (register int iter = 0; iter < reps; iter++) {
            for (register int i = 0; i < n; i++) {
                start = clock();
                factorial(levels[level_calc]);
                end = clock();

                float seconds = (float)(end - start) / CLOCKS_PER_SEC;
                values[i] = seconds;
            }
            
            double mean = float_mean(values, n);
            double median = float_median(values, n);
            double total = float_sum(values, n);

            write_results(fstream, HARDWARE_ID, CODE_ID, SO, n, (level_calc+1), (iter+1), total, mean, median, 0);
        }
    }
    free(values);
    fclose(fstream);
    return 0;
}