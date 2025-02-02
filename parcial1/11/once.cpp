#include <stdio.h>
#include <cstdlib>
#include "mpi.h"
using namespace std;

// solo considero 3 procesadores funcionando:
const int numworkers=3;

int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	int num_tasks;
	MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
	int task_id;
	MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

    if (task_id==0){ // master
		const int n=30;
		int a[n+1];
		printf("Primer vector:\n");
		for (int i=1; i<=n; i++) a[i]=rand()%100, printf("%d ", a[i]);
		printf("\n");
		printf("Segundo vector:\n");
		int b[n+1];
		for (int i=1; i<=n; i++) b[i]=rand()%100, printf("%d ", b[i]);
		printf("\n");

		const int tm1=(n+1)/2, tm2=n/2;
		// distribute the work:
		MPI_Send(&tm1,1,MPI_INT,1,3312,MPI_COMM_WORLD);
		for (int i=1; i<=n; i+=2) MPI_Send(&a[i],1,MPI_INT,1,3312,MPI_COMM_WORLD), MPI_Send(&b[i],1,MPI_INT,1,3312,MPI_COMM_WORLD);

		MPI_Send(&tm2,1,MPI_INT,2,3312,MPI_COMM_WORLD);
		for (int i=2; i<=n; i+=2) MPI_Send(&a[i],1,MPI_INT,2,3312,MPI_COMM_WORLD), MPI_Send(&b[i],1,MPI_INT,2,3312,MPI_COMM_WORLD);

	    int ans[n+1];
		for (int i=1; i<=n; i+=2){
			MPI_Recv(&ans[i],1,MPI_INT,1,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		for (int i=2; i<=n; i+=2){
			MPI_Recv(&ans[i],1,MPI_INT,2,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		printf("Suma de vectores:\n");
		for (int i=1; i<=n; i++) printf("%d ",ans[i]);
		printf("\n");
	}else{ // slaves 1,2
		int tm;
		MPI_Recv(&tm,1,MPI_INT,0,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		int partial[tm+1];
		for (int i=1; i<=tm; i++){
			int a,b;
			MPI_Recv(&a,1,MPI_INT,0,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&b,1,MPI_INT,0,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			partial[i]=a+b;
		}
		// return:
		for (int i=1; i<=tm; i++){
			MPI_Send(&partial[i],1,MPI_INT,0,3312,MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
	return 0;
}
