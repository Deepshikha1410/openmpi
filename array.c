#include<mpi.h>
#include<stdio.h>

int main(int argc, char **argv){
    int arr[10];
    int myid , numprocs;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if(myid==0){
       
        for(int i=0; i<10; i++){
		arr[i]=i;
	}
        MPI_Send(arr, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if(myid==1){
        MPI_Recv(arr, 10, MPI_INT, 0 , 0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("\nData Received : 1\n");
	for(int i =0; i<10;i++){
        printf("%d ",arr[i]);
	}
    }
   
    MPI_Finalize();
    return 0;
}
