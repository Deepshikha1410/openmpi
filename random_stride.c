#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "World size must be greater than 1 for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const int count = 3;       // Number of blocks
    const int blocklength = 1; // Number of elements in each block
    int stride;                // Random stride
    int data[15];              // Array to send/receive
    MPI_Datatype vector_type;

    // Seed the random number generator
    srand(time(NULL));

    // Generate a random stride between 1 and 10
    stride = (rand() % 10) + 1;

    // Create a vector datatype with the random stride
    MPI_Type_vector(count, blocklength, stride, MPI_INT, &vector_type);
    MPI_Type_commit(&vector_type);

    if (rank == 0) {
        // Initialize the data array with some values
        for (int i = 0; i < 15; i++) {
            data[i] = i + 1;
        }

        MPI_Send(data, 1, vector_type, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data: ");
        for (int i = 0; i < 15; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    } else if (rank == 1) {
        // Initialize the data array to zero
        for (int i = 0; i < 15; i++) {
            data[i] = 0;
        }

        MPI_Recv(data, 1, vector_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Shuffle the received data array
        for (int i = 0; i < 15; i++) {
            int j = (rand() % 15);
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }

        printf("Process 1 received data: ");
        for (int i = 0; i < 15; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    MPI_Type_free(&vector_type);
    MPI_Finalize();
    return 0;
}