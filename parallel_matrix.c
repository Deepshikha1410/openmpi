#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define SIZE 400
#define RESULT 40000 

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Allocate memory for matrices
    int **A = (int **)malloc(SIZE * sizeof(int *));
    int **B = (int **)malloc(SIZE * sizeof(int *));
    int **C = (int **)malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        A[i] = (int *)malloc(SIZE * sizeof(int));
        B[i] = (int *)malloc(SIZE * sizeof(int));
        C[i] = (int *)malloc(SIZE * sizeof(int));
    }

    // Initialize local matrices
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    // Start time
    double start_time = MPI_Wtime();

    // Perform local matrix multiplication
    for (int i = rank; i < SIZE; i += size) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Gather 
    MPI_Gather(C[0], SIZE * SIZE / size, MPI_INT, C[0], SIZE * SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // End time
    double end_time = MPI_Wtime();

    // Check condition
    if (rank == 0) {
        int sum = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                sum += C[i][j];
            }
        }
        if (sum == RESULT) {
            printf("correct\n");
        } else {
            printf("incorrect :\n");
        }
        printf("Execution Time: %f seconds\n", end_time - start_time);
    }

    // Free allocated memory
    for (int i = 0; i < SIZE; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    MPI_Finalize();
    return 0;
}