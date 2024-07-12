#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 400

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Allocate memory for local matrices
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

    // Scatter A and B matrices to all processes
    int *A_buf = (int *)malloc(SIZE * SIZE * sizeof(int));
    int *B_buf = (int *)malloc(SIZE * SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A_buf[i * SIZE + j] = A[i][j];
            B_buf[i * SIZE + j] = B[i][j];
        }
    }
    MPI_Scatter(A_buf, SIZE * SIZE / size, MPI_INT, A[0], SIZE * SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B_buf, SIZE * SIZE / size, MPI_INT, B[0], SIZE * SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local matrix multiplication
    for (int i = rank * SIZE / size; i < (rank + 1) * SIZE / size; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Gather C matrices from all processes
    int *C_buf = (int *)malloc(SIZE * SIZE * sizeof(int));
    MPI_Gather(C[0], SIZE * SIZE / size, MPI_INT, C_buf, SIZE * SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Print result on process 0
    if (rank == 0) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", C_buf[i * SIZE + j]);
            }
            printf("\n");
        }
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
    free(A_buf);
    free(B_buf);
    free(C_buf);

    MPI_Finalize();
    return 0;
}