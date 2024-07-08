//Prime number using MPI_TYPE_VECTOR
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int count = 5;
    int primes[count];
    MPI_Datatype vector_type;

    // Create a vector datatype to represent the array of primes
    MPI_Type_vector(count, 1, 1, MPI_INT, &vector_type);
    MPI_Type_commit(&vector_type);

    if (rank == 0) {
        // Generate prime numbers and store them in the primes array
        int num = 2;
        for (int i = 0; i < count; i++) {
            while (!is_prime(num)) num++;
            primes[i] = num++;
        }

        // Send the primes array to process 1
        MPI_Send(primes, 1, vector_type, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // Receive the primes array from process 0
        MPI_Recv(primes, 1, vector_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Print the received prime numbers
        printf("Received prime numbers: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", primes[i]);
        }
        printf("\n");
    }

    MPI_Type_free(&vector_type);
    MPI_Finalize();
    return 0;
}