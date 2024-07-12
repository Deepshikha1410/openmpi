//Matrix multiplication using boadcast and scatter
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 400

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

    if (rank == 0) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                A[i][j] = 1;
                B[i][j] = 1;
                C[i][j] = 0;
            }
        }
    }

    MPI_Bcast(A[0], SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B[0], SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    //scatter matrix A 
    int *A_new = (int *)malloc(SIZE * SIZE / size * sizeof(int));
    MPI_Scatter(A[0], SIZE * SIZE / size, MPI_INT, A_new, SIZE * SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // scatter matrix B to 
    int *B_new = (int *)malloc(SIZE * SIZE / size * sizeof(int));
    MPI_Scatter(B[0], SIZE * SIZE / size, MPI_INT, B_new, SIZE * SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // matrix multiplication
    for (int i = rank; i < SIZE; i += size) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A_local[i * SIZE / size + k] * B_local[k * SIZE / size + j];
            }
        }
    }

    
    MPI_Gather(C[0], SIZE * SIZE / size, MPI_INT, C[0], SIZE * SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Print result on process 0
    if (rank == 0) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", C[i][j]);
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
    free(A_local);
    free(B_local);

    MPI_Finalize();
    return 0;
}