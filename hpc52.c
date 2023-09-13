#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 3 // Number of rows in matrices A and C
#define M 4 // Number of columns in matrix A and rows in matrix B
#define P 2 // Number of columns in matrices B and C

void matrixMultiply(int A[N][M], int B[M][P], int C[N][P]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0; // Initialize the result element to 0
            for (int k = 0; k < M; k++) {
                C[i][j] += A[i][k] * B[k][j]; // Matrix multiplication
            }
        }
    }
}

int main() {
    int A[N][M], B[M][P], C[N][P];

    // Initialize matrices A and B with sample values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = i * M + j + 1;
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            B[i][j] = i * P + j + 1;
        }
    }

    // Perform matrix multiplication using OpenMP
    matrixMultiply(A, B, C);

    // Display the result matrix C
    printf("Matrix C (Result of A x B):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
