#include <stdio.h>

int suma(int a, int b){
	return a+b;
}

int resta(int a, int b){
	return a-b;
}

int mul(int a, int b){
	return a*b;
}

int divi(int a, int b){
	return a/b;
}

int main(){
	int a,b;
	a=20,b=5;
	printf("%d\n",suma(a,b));
	printf("%d\n",resta(a,b));
	printf("%d\n",mul(a,b));
	printf("%d\n",divi(a,b));

	return 0;
}
