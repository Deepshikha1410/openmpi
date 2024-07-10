#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr,"World size must be greater than 1 for this example\n");
        MPI_Abort( MPI_COMM_WORLD , 1);
    }

    if (rank != 0) {
        int data = 100;
        MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        MPI_Status status;
        int data = 0;  

        MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD, &status);
        printf("Process 0 received data from process %d\n", status.MPI_SOURCE,i);

    }

    MPI_Finalize();

    return 0;
}
 

























































 