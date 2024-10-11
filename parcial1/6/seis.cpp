#include <stdio.h>
#include <math.h>
#include "mpi.h"
using namespace std;

// solo considero 3 procesadores funcionando:
const int numworkers=3;

const int numterms_fib=80; // los numeros fibonacci crecen rapido
const int divi=numterms_fib/numworkers;
const int modu=numterms_fib%numworkers;

const double phi=((double)sqrt(5)+1)/2;

double f(int n){
	return ((double)pow(phi,n)-pow((double)-1/phi,n))/sqrt(5);
}

int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	int num_tasks;
	MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
	int task_id;
	MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

	double a,b,c;

	if (task_id==0){
		a=f(0),b=f(1);
		for (int i=0; i<divi; i++){
			printf("%llu ",(unsigned long long)a);
			c=a+b;
			a=b;
			b=c;
		}
	}else{
		int nlocal=divi;
		if (task_id<=modu) nlocal++;

		int n1=divi; // w0 does [0,divi-1]
		for (int i=1; i<task_id; i++){
			if (i<=modu) n1+=divi+1;
			else n1+=divi;
		}
		
		a=f(n1), b=f(n1+1);
		for (int i=0; i<nlocal; i++){
			printf("%llu ",(unsigned long long)a);
			c=a+b;
			a=b;
			b=c;
		}
	}
	printf("fin del trabajo %d\n", task_id);
	MPI_Finalize();
	return 0;
}
// se compila con:
// mpic++ seis.cpp -o seis
// se corre con:
// mpirun -np 3 ./seis
