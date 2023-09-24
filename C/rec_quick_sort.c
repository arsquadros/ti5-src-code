#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "general.c"

#define CODE_ID 5

#define HARDWARE_ID -1 // edit to your id
#define SO -1 // edit to so's id

const int levels[] = {1, 2, 3};

void fill_random(int *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand();
    }
}

void swap(int *v, int i, int j) {
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void rec_quicksort(int *v, int left, int right) {
    int i = left, j = right;
    int pivot = v[(right + left)/2];
    while (i <= j) {
        while (v[i] < pivot) { i++; }
        while (v[j] > pivot) { j--; }
        if (i <= j) {
            swap(v, i++, j--);
        }
    }
    if (left < j)  rec_quicksort(v, left, j);
    if (i < right)  rec_quicksort(v, i, right);
}

void quicksort(int *v, int n) {
    rec_quicksort(v, 0, n-1);
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
                fill_random(v, (n * levels[level_calc]));

                start = clock();
                quicksort(v, (n * levels[level_calc]));
                end = clock();

                float seconds = (float)(end - start) / CLOCKS_PER_SEC;
                values[i] = seconds;
            }

            double mean = float_mean(values, (100));
            double median = float_median(values, (100));
            double total = float_sum(values, (100));

            write_results(fstream, HARDWARE_ID, CODE_ID, SO, 100, (level_calc+1), (iter+1), total, mean, median);
        }
    }
    
    fclose(fstream);

    return 0;
}