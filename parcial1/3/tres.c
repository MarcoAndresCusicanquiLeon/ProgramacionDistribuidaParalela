#include <stdio.h>

void suma(int *a, int *b, int *res){
	*res=(*a)+(*b);
}

void resta(int *a, int *b, int *res){
	*res=(*a)-(*b);
}

void mul(int *a, int *b, int *res){
	*res=(*a)*(*b);
}

void divi(int *a, int *b, int *res){
	*res=(*a)/(*b);
}

int main(){
	int a,b;
	a=20,b=5;
	int c;
	suma(&a,&b,&c);
	printf("%d\n",c);
	resta(&a,&b,&c);
	printf("%d\n",c);
	mul(&a,&b,&c);
	printf("%d\n",c);
	divi(&a,&b,&c);
	printf("%d\n",c);

	return 0;
}
