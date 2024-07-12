#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <pthread.h>

#define NUM_THREADS 4

void *hello_world(void *arg) {
  int thread_id = *(int *)arg;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  printf("Hello, world! thread %d rank %d\n", thread_id, rank);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  pthread_t threads[NUM_THREADS];
  int thread_id[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++) {
    thread_id[i] = i;
    pthread_create(&threads[i], NULL, hello_world, (void *)&thread_id[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  MPI_Finalize();
  return 0;
}
