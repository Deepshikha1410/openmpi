#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int rank, size, chunk_size;
    int *data, *local_data, *local_sum;
    int overall_sum = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);
    data = (int *)malloc(10000 * sizeof(int));
    for (int i = 0; i < 10000; i++) {
        data[i] = rand() % 100;
    }

    chunk_size = 10000 / size;

    local_data = (int *)malloc(chunk_size * sizeof(int));
    local_sum = (int *)malloc(sizeof(int));

   
    MPI_Scatter(data, chunk_size, MPI_INT, local_data, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    *local_sum = 0;
    for (int i = 0; i < chunk_size; i++) {
        *local_sum += local_data[i];
    }
    MPI_Gather(local_sum, 1, MPI_INT, NULL, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        overall_sum = 0;
        for (int i = 0; i < size; i++) {
            MPI_Recv(local_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            overall_sum += *local_sum;
        }
        printf("Overall sum: %d\n", overall_sum);
    }

    MPI_Finalize();

    return 0;
}