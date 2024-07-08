#include <stdio.h>
#include <mpi.h>
#define N 10

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int localsum = 0;
    int Totalsum = 0;
    
    for (int i = rank; i < N; i += size) {
        localsum += i;
    }

   
    MPI_Reduce(&localsum, &Totalsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total sum: %d\n", Totalsum);
    }

    MPI_Finalize();

    return 0;
}