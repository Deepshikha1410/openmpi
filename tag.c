#include<mpi.h>
#include<stdio.h>

int main(int argc , char **argv)
{
	MPI_Init(&argc , &argv);

        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD , &rank);

        int size;
        MPI_Comm_size(MPI_COMM_WORLD , &size);

        if(size < 2) 
        {
            fprintf(stderr , " world size  must be  greater than 1 for this example \n");
            MPI_Abort(MPI_COMM_WORLD , 1);
        }

        int n1,n2;
        if(rank == 0)
        {
            n1 = 100;
            n2 = 200;
            MPI_Request request;
            MPI_Isend(&n1 , 1 , MPI_INT , 1 , 0 , MPI_COMM_WORLD , &request);
            MPI_Isend(&n2 , 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);      //to avoid the non synchornization then use different tag

            MPI_Wait(&request , MPI_STATUS_IGNORE);

            printf("proces 0 sent number %d to process 1 \n", n1);

            printf("proces 0 sent number %d to process 2 \n", n2);
         }
        
        else if(rank == 1)
         {
            MPI_Request request;
            
                MPI_Irecv(&n1 , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &request);
                MPI_Wait(&request , MPI_STATUS_IGNORE);
                MPI_Irecv(&n2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request );
                MPI_Wait(&request , MPI_STATUS_IGNORE);
                printf("process 1 receive number %d from process 0 \n ", n1);
                printf("process 2 receive number %d from process 0 \n ", n2);
            
         }
         else {
                printf("I am process %d and I have nothing to do\n",rank);
         }
            MPI_Finalize();
            return 0;

        
    }
    