#include <stdio.h>
#include <malloc.h>

void f(int* q){
	*q = 1000;
}
int main(void){

	int* p = (int*)malloc(sizeof(int));
	*p = 10;
	printf("%d\n", *p);
	f(p);
	printf("%d\n", *p);
	free(p);
	return 0;
}