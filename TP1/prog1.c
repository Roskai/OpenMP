#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define VALMAX 31

int main (void){
	int i;

	
	
	#pragma omp parallel for num_threads(4), schedule(static,3)
	for(i=0;i<VALMAX;i++){
		printf("%02d = %d\n",i ,omp_get_thread_num());
		// if (i%2==0) //si i divisible par 2
	}
	return 0;
}

