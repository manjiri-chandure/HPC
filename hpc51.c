#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 5  // Size of the matrices

void sumLowerTriangularMatrices(int A[][N], int B[][N], int C[][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Initialize matrices A and B (assuming lower triangular)
    // For simplicity, we use random values here.
    srand(1234);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            A[i][j] = rand() % 10; // get number between 0 to 9
            B[i][j] = rand() % 10;
        }
    }

    // Sum the matrices using OpenMP
    sumLowerTriangularMatrices(A, B, C);

    // Display the result matrix C (sum of A and B)
    printf("Matrix C (Sum of A and B):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
