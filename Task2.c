#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void perform_computation(int rank) {
    printf("Process %d performing computation\n", rank);
    // Simulate computation by sleeping for a while
    sleep(2);
}

void perform_io_operations(int rank) {
    printf("Process %d performing I/O operations\n", rank);
    // Simulate I/O by sleeping for a while
    sleep(3);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int color = world_rank % 2;
    MPI_Comm even_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &even_comm);

    if (color == 0) {
        perform_io_operations(world_rank);
    } else {
        perform_computation(world_rank);
    }

  
    if (even_comm != MPI_COMM_NULL) MPI_Comm_free(&even_comm);
    

    MPI_Finalize();

    return 0;
}
