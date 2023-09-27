#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "general.c"

#define CODE_ID 4

#define HARDWARE_ID -1 // edit to your id
#define SO -1 // edit to so's id

const int levels[] = {1, 2, 3};

void swap(int *v, int i, int j) {
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void selectionSort(int *v, int n) {
    int sm = 0;

    for (int i = 0; i < n - 1; i++) {
        sm = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[sm]) {
                sm = j;
            }
        }
        swap(v, i, sm);
    }
}



int main(int argc, char *argv[]) {
    FILE *fstream = fopen(FILEPATH, "w");

    clock_t start, end;

    char *tmp = argv[1];
    register int n = 0;
    sscanf(argv[1], "%d", &n);

    srand(time(NULL));
    int *v = (int*)malloc((n * levels[2]) * sizeof(int));

    float *values = (float *)malloc(100 * sizeof(float));

    start_results(fstream);
    for (register int level_calc = 0; level_calc < 3; level_calc++) {
        for (register int iter = 0; iter < reps; iter++) {
            for(register int i = 0; i < 100; i++) {
                fill_random_vector(v, (n * levels[level_calc]));

                start = clock();
                selectionSort(v, (n * levels[level_calc]));
                end = clock();

                float seconds = (float)(end - start) / CLOCKS_PER_SEC;
                values[i] = seconds;
            }

            double mean = float_mean(values, 100);
            double median = float_median(values, 100);
            double total = float_sum(values, 100);

            write_results(fstream, HARDWARE_ID, CODE_ID, SO, 100, level_calc, (iter+1), total, mean, median, (n * levels[level_calc]));
        }
    }

    fclose(fstream);
    return 0;
}