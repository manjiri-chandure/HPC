#include <stdio.h>
#include <omp.h>

#define VECTOR_SIZE 200
#define SCALAR 5

int main() {
    int vector[VECTOR_SIZE];
    int result[VECTOR_SIZE];
    int chunk_sizes[] = {1, 5, 10, 20, 50}; // Varying chunk sizes

    // Initialize the vector with some values
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = i;
        result[i] = 0;
    }

    printf("Vector size: %d\n", VECTOR_SIZE);

    // Static schedule with varying chunk sizes
    printf("Static Schedule:\n");
    for (int i = 0; i < sizeof(chunk_sizes) / sizeof(chunk_sizes[0]); i++) {
        int chunk = chunk_sizes[i];
        double start_time = omp_get_wtime();

        #pragma omp parallel for schedule(static, chunk) num_threads(4)
        for (int j = 0; j < VECTOR_SIZE; j++) {
            result[j] = vector[j] + SCALAR;
        }

        double end_time = omp_get_wtime();
        printf("Chunk size %d, Time: %f seconds\n", chunk, end_time - start_time);
    }

    // Reset result array
    for (int i = 0; i < VECTOR_SIZE; i++) {
        result[i] = 0;
    }

    // Dynamic schedule with varying chunk sizes and nowait clause
    printf("Dynamic Schedule with Nowait Clause:\n");
    for (int i = 0; i < sizeof(chunk_sizes) / sizeof(chunk_sizes[0]); i++) {
        int chunk = chunk_sizes[i];
        double start_time = omp_get_wtime();

        #pragma omp parallel num_threads(4)
        {
            #pragma omp for schedule(dynamic, chunk) nowait
            for (int j = 0; j < VECTOR_SIZE; j++) {
                result[j] = vector[j] + SCALAR;
            }
        } // No wait here

        double end_time = omp_get_wtime();
        printf("Chunk size %d, Time: %f seconds\n", chunk, end_time - start_time);
    }

    return 0;
}
