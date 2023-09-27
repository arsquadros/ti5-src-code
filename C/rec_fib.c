#include <stdio.h>
#include <time.h>

#include "general.c"

#define CODE_ID 3

#define HARDWARE_ID -1 // edit to your id
#define SO -1 // edit to so's id

const long long levels[] = {20LL, 30LL, 40LL};

long long rec_fib(long long n, long long i) {
    if (i == 0) { return 0; }
    else if (i == 1) { return 1; }
    else if (i >= 2) {
        return rec_fib(n, i - 1) + rec_fib(n, i - 2);
    } else {
        return -1;
    }
}

long long fib(long long n) {
    return rec_fib(n, n);
}

int main(void) {
    FILE *fstream = fopen(FILEPATH, "w");

    register int n = 100;
    clock_t start, end;
    
    float *values = (float *)malloc(n * sizeof(float));

    start_results(fstream);

    for (register int level_calc = 0; level_calc < 3; level_calc++) {
        for (register int iter = 0; iter < reps; iter++) {
            for (register int i = 0; i < n; i++) {
                start = clock();
                fib(levels[level_calc]);
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
    fclose(fstream);

    return 0;
}