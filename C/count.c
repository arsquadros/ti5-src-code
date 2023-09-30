#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "general.c"

#define CODE_ID 1

#define HARDWARE_ID -1 // edit to your id
#define SO -1 // edit to so's id

const float levels[] = {1, 1.5, 2};

int main(void) {
    FILE *fstream = fopen(FILEPATH, "w");

    register int limit = 1000000000; // billion

    register int n = 100;
    float *values = (float *)malloc(n * sizeof(float));

    register int counter;
    clock_t start, end;

    start_results(fstream);
    for (register int level_calc = 0; level_calc < 3; level_calc++) {
        for (register int iter = 0; iter < reps; iter++) {
            for (register int i = 0; i < n; i++) {
                counter = 0;
                register int new_limit = (int)(limit * levels[level_calc]);

                start = clock();
                while (counter < new_limit) {
                    counter++;
                }
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