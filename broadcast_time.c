#include<mpi.h>
#include<stdio.h>

int main(int argc, char**argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank( MPI_COMM_WORLD ,&rank);

    int data1,data2;

    double start_time, end_time;
     // Start timing the computation
        start_time = MPI_Wtime();

    if (rank==0) {
        data1 = 100;
        data2 = 200; //Root process initalizes the data
    }

    //Broadcat the data from the root process to all process
    MPI_Bcast( &data1 , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
    MPI_Bcast( &data2 , 1 , MPI_INT , 0 , MPI_COMM_WORLD);

    printf("Process %d received data %d\n",rank,data1);

    printf("Process %d received data %d\n",rank,data2);


    // Stop timing the computation
    end_time = MPI_Wtime();
    // printf("The total sum of array elements is %ld\n", final_sum);
    printf("Time taken: %f seconds\n", end_time - start_time);

    MPI_Finalize();
    return 0;
}