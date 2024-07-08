#include<mpi.h>
#include<stdio.h>

int main(int argc, char **argv){
    int myid, numprocs;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    int myval;

    if(myid==0){
        myval = 100;
        printf("\nmyid: %d \t myval=%d",myid, myval);
        MPI_Ssend(&myval, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("\nmyid: %d \t Data sent.\n",myid);
    }
    else if(myid==1){
        myval = 200;
        MPI_Recv(&myval, 1, MPI_INT, 0 , 0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("\nmyid: %d \t Data received.",myid);
        printf("\nmyid: %d \t myval=%d",myid,myval);
    }
    printf("\n\nProgram exit !\n");
    MPI_Finalize();
    return 0;
}