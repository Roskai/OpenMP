#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define VALMAX 34

int main(void)
{

	int i, j, itThreads[4];

	for (i = 0; i < 4; i++)
	{
		itThreads[i] = 0;
	}

#pragma omp parallel for num_threads(4) private(j), schedule(static, 1)
	for (i = 0; i < 40; i++)
	{
		for (j = 0; j < i; j++)
		{
			itThreads[omp_get_thread_num()]++;
		}
	}

	int nbTotal = 0;
	for (i = 0; i < 4; i++)
	{
		nbTotal += itThreads[i];
		printf("%d %d\n", i, itThreads[i]);
	}
	printf("Nombre total = %d, nombre moyen par threads : %d\n", nbTotal, nbTotal/4 /* il y 4 threads*/);

}
