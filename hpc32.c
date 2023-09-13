#include <stdio.h>
#include <omp.h>

#define matrixsize 300

int main() {
    int matrix1[matrixsize][matrixsize];
    int matrix2[matrixsize][matrixsize];
    int result[matrixsize][matrixsize];

    // Initialize matrices with some values
    for (int i = 0; i < matrixsize; i++) {
        for (int j = 0; j < matrixsize; j++) {
            matrix1[i][j] = i + j;
            matrix2[i][j] = i - j;
        }
    }

    double start_time_serial = omp_get_wtime();

    // Serial matrix addition
    for (int i = 0; i < matrixsize; i++) {
        for (int j = 0; j < matrixsize; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    double end_time_serial = omp_get_wtime();
    printf("Serial Time: %f seconds\n", (end_time_serial - start_time_serial));

    // Reset result matrix
    for (int i = 0; i < matrixsize; i++) {
        for (int j = 0; j < matrixsize; j++) {
            result[i][j] = 0;
        }
    }

    double start_time_parallel = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic) num_threads(8) collapse(2) ordered 
    for (int i = 0; i < matrixsize; i++) {
        for (int j = 0; j < matrixsize; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    double end_time_parallel = omp_get_wtime();
    printf("Parallel Time: %f seconds\n", (end_time_parallel - start_time_parallel));

    return 0;
}
