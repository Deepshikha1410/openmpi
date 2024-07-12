#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int thread_provided;
  int provided =MPI_THREAD_MULTIPLE;
  int thread_level = MPI_Init_thread(&argc , &argv , provided , &thread_provided);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (thread_level != MPI_SUCCESS)
  {
    printf("eOOR INITIALISE MPI threads\n");
    return 1;
  }
  
  if (thread_provided != MPI_THREAD_MULTIPLE)
  {
    printf("warning : MPI_THREAD_MULTIPLR requested but not provided\n");

  }
  
  #pragma omp parallel
  {

    int thread_num = omp_get_thread_num();

    
    printf("Hello from process %d, thread %d\n", rank, thread_num);
  }

  
  MPI_Finalize();

  return 0;
}