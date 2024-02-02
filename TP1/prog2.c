#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define VALMAX 32

int main (void){
	int i,temp;    
	printf("%d nombre max de threads\n",omp_get_max_threads());
    #pragma omp parallel for num_threads(4),private(temp)
	for(i=0;i<VALMAX;i++){
		temp = i%2;
        #pragma omp if: usleep(1) 
		if (!temp) //si i divisible par 2
			printf("pour i=%02d, resultat pair, trouve par %d\n",i,omp_get_thread_num());
	}
	return 0;
}
