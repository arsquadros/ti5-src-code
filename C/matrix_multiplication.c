#include <stdio.h>
#include <time.h>

#include "general.c"

#define CODE_ID 6

#define HARDWARE_ID -1 // edit to your id
#define SO -1 // edit to so's id

const float levels[] = {1.0f, 1.5f, 2.0f};

int **matrix_multiplication(int **m1, int **m2, int **result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int pos_result = 0;
            for (int k = 0; k < n; k++) {
                pos_result += m1[i][k] * m2[k][j];
            }
            result[i][j] = pos_result;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    FILE *fstream = fopen(FILEPATH, "w");

    char *tmp = argv[1];
    int n = 0;
    sscanf(argv[1], "%d", &n);

    srand(time(NULL));
    int **result = (int **)malloc((int)((n * levels[2])) * sizeof(int *));
    int **m1 = (int**) malloc((int)((n * levels[2])) * sizeof(int *));
    int **m2 = (int**) malloc((int)((n * levels[2])) * sizeof(int *));
    for (int i = 0; i < (int)((n * levels[2])); i++) {
        m1[i] = (int*) malloc((int)((n * levels[2])) * sizeof(int));
        m2[i] = (int*) malloc((int)((n * levels[2])) * sizeof(int));
        result[i] = (int *)malloc((int)((n * levels[2])) * sizeof(int));
    }
    
    clock_t start, end;

    start_results(fstream);
    float *values = (float *)malloc(100 * sizeof(float));
    for (register int level_calc = 0; level_calc < 3; level_calc++) {
        for (register int iter = 0; iter < reps; iter++) {
            for (register int i = 0; i < 100; i++) {
                fill_random_matrix(m1, ((int)((n * levels[level_calc]))));
                fill_random_matrix(m2, ((int)((n * levels[level_calc]))));
            
                start = clock();
                matrix_multiplication(m1, m2, result, ((int)((n * levels[level_calc]))));
                end = clock();
                
                float seconds = (float)(end - start) / CLOCKS_PER_SEC;
                values[i] = seconds;
            }

            double mean = float_mean(values, 100);
            double median = float_median(values, 100);
            double total = float_sum(values, 100);

            write_results(fstream, HARDWARE_ID, CODE_ID, SO, 100, level_calc, (iter+1), total, mean, median, ((int)((n * levels[level_calc]))));
        }
    }
    for (int i = 0; i < (int)((n * levels[2])); i++) {
        free(m1[i]); free(m2[i]); free(result[i]);
    }
    free(m1); free(m2); free(result); free(values);
    fclose(fstream);
    return 0;
}