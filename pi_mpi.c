#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>
#include<mpi.h>

#define N 999999999


int main(int argc, char** argv) {
    int i, j, rank, size;
    double area, pi, dx, y, x;
    double exe_time, local_area;
    struct timeval start_time, stop_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    dx = 1.0/N;
    x = 0.0;
    local_area = 0.0;
    int chunk_size = N/size;
    int chunk_start = rank * chunk_size;
    int chunk_end = (rank + 1) * chunk_size;
    if(chunk_end > N) {
        chunk_end = N;
    } 

    gettimeofday(&start_time, NULL);

    for(i=chunk_start;i<chunk_end;i++) {
        x = i*dx;
        y = sqrt(1-x*x);
        local_area += y*dx;
    }

    MPI_Reduce(&local_area, &area, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    gettimeofday(&stop_time, NULL);

    exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));

    if(rank == 0) {
        pi = 4.0*area;
        printf("\n Value of pi is = %.16lf\n Execution time is = %lf seconds\n", pi, exe_time);
    }

    MPI_Finalize();

    return 0;
}
