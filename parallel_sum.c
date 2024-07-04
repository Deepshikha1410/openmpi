#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_sum = 0;
    int total_sum = 0;
    int *data;
    int data_size = 100;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    data = (int *)malloc(data_size * sizeof(int));

    for (int i = 0; i < data_size; i++) {
        data[i] = i + 1;
    }

    for (int i = 0; i < data_size; i++) {
        local_sum += data[i];
    }

    if (rank != 0) {
        MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < size; i++) {
            int received_sum;
            MPI_Recv(&received_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_sum += received_sum;
        }
    
        total_sum += local_sum;

        printf("Total sum: %d\n", total_sum);
    }

    MPI_Finalize();
    free(data);

    return 0;
}