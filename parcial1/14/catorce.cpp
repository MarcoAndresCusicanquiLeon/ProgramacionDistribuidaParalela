#include <stdio.h>
#include <cstdlib>
#include "mpi.h"
using namespace std;

// solo considero 3 procesadores funcionando:
const int numworkers=3;

const int n=5; // mtr size

int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	int num_tasks;
	MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
	int task_id;
	MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

	if (task_id==0){ // master
		int m1[n+1][n+1], m2[n+1][n+1];
		for (int i=1; i<=n; i++){
			for (int j=1; j<=n; j++){
				m1[i][j]=rand()%100 +1;
				m2[i][j]=rand()%100 +1;
			}
		}

		printf("Matriz1:\n");
		for (int i=1; i<=n; i++){
			for (int j=1; j<=n; j++){
				printf("%d ", m1[i][j]);
			}
			puts("");
		}
		printf("Matriz2:\n");
		for (int i=1; i<=n; i++){
			for (int j=1; j<=n; j++){
				printf("%d ", m2[i][j]);
			}
			puts("");
		}

		// use a chessboard distribution for slaves 1/2:
		for (int i=1; i<=n; i++){
			for (int j=1; j<=n; j++){
				// row i m1 * col j m2:
				if ((i+j)&1){
					for (int k=1; k<=n; k++) MPI_Send(&m1[i][k],1,MPI_INT,1,3312,MPI_COMM_WORLD);
					for (int k=1; k<=n; k++) MPI_Send(&m2[k][j],1,MPI_INT,1,3312,MPI_COMM_WORLD);
				}else{
					for (int k=1; k<=n; k++) MPI_Send(&m1[i][k],1,MPI_INT,2,3312,MPI_COMM_WORLD);
					for (int k=1; k<=n; k++) MPI_Send(&m2[k][j],1,MPI_INT,2,3312,MPI_COMM_WORLD);
				}
			}
		}

		printf("Resultado:\n");
		for (int i=1; i<=n; i++){
			for (int j=1; j<=n; j++){
				int ansij;
				if ((i+j)&1){
					MPI_Recv(&ansij,1,MPI_INT,1,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				}else{
					MPI_Recv(&ansij,1,MPI_INT,2,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				}
				printf("%d ", ansij);
			}
			puts("");
		}
	}else{ // slaves 1,2
		int row[n+1], col[n+1];
		int sz;
		if (task_id==1) sz=n*n/2; // ev
		else sz=(n*n+1)/2;
		int aux[sz];
		for (int ite=0; ite<sz; ite++){
			for (int i=1; i<=n; i++) MPI_Recv(&row[i],1,MPI_INT,0,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			for (int i=1; i<=n; i++) MPI_Recv(&col[i],1,MPI_INT,0,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			int temp=0;
			for (int i=1; i<=n; i++){
				temp+=row[i]*col[i];
			}
			aux[ite]=temp;
		}

		for (int ite=0; ite<sz; ite++){
			MPI_Send(&aux[ite],1,MPI_INT,0,3312,MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
	return 0;
}
