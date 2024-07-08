#include<mpi.h>
#include<stdio.h>

int main(int argc , char **argv)
{
	MPI_Init(&argc , &argv);

        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD , &rank);

        int size;
        MPI_Comm_size(MPI_COMM_WORLD , &size);

        int sendBuf, recvBuf;

        if(rank == 0)
        {
            sendBuf = 100;
            MPI_Sendrecv( &sendBuf , 1 , MPI_INT , 1 , 0 , &recvBuf , 1 , MPI_INT , 1 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            printf("process 0 sent number %d and received number %d \n", sendBuf, recvBuf);
         }
        
        else if(rank == 1)
         {
            sendBuf = 200;
            MPI_Sendrecv( &sendBuf , 1 , MPI_INT , 0 , 0 , &recvBuf , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            printf("process 1 receive number %d and sent number %d\n", sendBuf,recvBuf);
            
         }else{
            printf("I am process %d and I have nothing to do\n",rank);
         }
        MPI_Finalize();
        return 0;

        
    }

    MPI_Sendrecv_replace( void* buf , MPI_Count count , MPI_Datatype datatype , int dest , int sendtag , int source , int recvtag , MPI_Comm comm , MPI_Status* status); 