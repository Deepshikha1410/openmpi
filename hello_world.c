#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>


int main(int argc, char** argv) {
      int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    #pragma omp parallel
     {
        printf("Hello World\n");
    }

    MPI_Finalize();
    return 0;

}