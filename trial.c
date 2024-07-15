#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc , &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 1000
    long *array = NULL;
    int chunk_size = n / size;
    long *sub_array = (long*)malloc(chunk_size * sizeof(long));

    if(rank==0) {
        array = (long*)malloc(n * sizeof(long));
        for (int i = 0; i < n ; i++) {
            array[i] = i + 1; //Initialize the array with value
        }
    }

    
}