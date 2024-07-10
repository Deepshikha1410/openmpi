
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<sys/time.h>
#include<mpi.h>

#define N 1000

int main(int argc, char** argv) {
    int i, j;
    int count, flag,count1;
    double exe_time;
    struct timeval start_time, stop_time;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    count1 = 1;
    int chunk_size = N/size;
    int chunk_start = rank * chunk_size;
    int chunk_end = (rank + 1) * chunk_size;
    if(chunk_end > N) {
        chunk_end = N;
    } 


    gettimeofday(&start_time, NULL);

    for(i = chunk_start; i < chunk_end; i += 1) {
        flag = 0;
        for(j = 2; j < i; j++) {
            if((i % j) == 0) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            count++;
        }
    }

    MPI_Reduce(&count, &count1, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        gettimeofday(&stop_time, NULL);
        exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));
        printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", count1-2, exe_time);
    }

    MPI_Finalize();

    return 0;
}
