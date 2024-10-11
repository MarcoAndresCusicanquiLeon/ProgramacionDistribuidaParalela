#include <stdio.h>
#include <cstdlib>
#include <string>
#include "mpi.h"
using namespace std;
#define pb push_back

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
		string a[n+1];
		printf("Las cadenas son:\n");
		for (int i=1; i<=n; i++){
			int sz_str=rand()%10 +4;
			string curr_str="";
			for (int j=0; j<sz_str; j++) curr_str.pb(rand()%26 +'a');
			puts(curr_str.c_str());
			a[i]=curr_str;
		}

		printf("distribuyendo a los esclavos se tiene:\n");
		const int tm2=(n+1)/2, tm1=n/2;
		
		MPI_Send(&tm1,1,MPI_INT,1,3312,MPI_COMM_WORLD);
		MPI_Send(&tm2,1,MPI_INT,2,3312,MPI_COMM_WORLD);
		for (int i=1; i<=n; i++){
			int sz_str=a[i].size();
			if (i&1) MPI_Send(&sz_str,1,MPI_INT,2,3312,MPI_COMM_WORLD), MPI_Send(a[i].c_str(),sz_str,MPI_CHAR,2,3312,MPI_COMM_WORLD);
			else MPI_Send(&sz_str,1,MPI_INT,1,3312,MPI_COMM_WORLD), MPI_Send(a[i].c_str(),sz_str,MPI_CHAR,1,3312,MPI_COMM_WORLD);
		}
	}else{ // slaves 1,2
		int tm;
		MPI_Recv(&tm,1,MPI_INT,0,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		for (int i=0; i<tm; i++){
			int sz_str;
			MPI_Recv(&sz_str,1,MPI_INT,0,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			string curr_str(sz_str,64);
			MPI_Recv(&curr_str[0],sz_str,MPI_CHAR,0,3312,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			puts(curr_str.c_str());
		}
		printf("\n");
	}

	MPI_Finalize();
	return 0;
}
