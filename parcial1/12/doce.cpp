#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <functional>
typedef unsigned long long ull;

const int numterms_fib=80; // los numeros fibonacci crecen rapido
ull ans[numterms_fib];
ull ans_local;

const double phi=((double)sqrt(5)+1)/2;

int main(){
#pragma omp parallel for private(ans_local) shared(phi,numterms_fib,ans)
	for (int i=0; i<numterms_fib; i++){
		std::function< double(int) > f = [](int n){
			return ((double)pow(phi,n)-pow((double)-1/phi,n))/sqrt(5);
		};
		ans_local=f(i);
		printf("fibo[%d] = %llu\n", i,ans_local);
		ans[i]=ans_local;
	}
	printf("ahora mostrando los numeros en orden:\n");
	for (int i=0; i<numterms_fib; i++) printf("%llu ",ans[i]);
	printf("\n");

	return 0;
}
