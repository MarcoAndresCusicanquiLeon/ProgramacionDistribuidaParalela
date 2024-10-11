#include <stdio.h>
#include <math.h>

// se utiliza la formula area del circulo unitario:
// 2 * integral[-1,1] (sqrt(1-x^2)) dx
// se separa el rango [-1,1] en al menos 10^5 partes

const int npartes=100000;
const double DX=(double)2/npartes;

double f(double &x){
	return sqrt((double)1-x*x);
}

void integra(double *res, double *x, int stepno){
	//printf("step: %d\n",stepno);
	if (stepno==0) return;
	*res+=f(*x)*DX;
	*x+=DX;
	integra(res,x,stepno-1);
}

int main(){
	double PI=0.0;
	// iterativo:
	double x=-1.0;
	for (int i=0; i<npartes; i++, x+=DX){
		PI+=f(x)*DX;
	}
	PI*=2;

	printf("Calculo de PI Iterativo: %.10lf\n", PI);

	// recursivo:

	double *PIrec=&PI;
	*PIrec=0.0;
	double xcurr=-1.0;
	integra(PIrec,&xcurr,npartes);
	PI*=2;
	printf("Calculo de PI Recursivo: %.10lf\n", PI);

	return 0;
}
