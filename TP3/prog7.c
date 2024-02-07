#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define DIM2 10000000
#define DIM1 9
#define NB_TEST 3

double A[DIM1][DIM2], B[DIM1][DIM2], C[DIM1][DIM2];

int main(void)
{

	int i, j;
	double res;
	double tmpSeq, tmpPar, acceleration, efficacite;
	double start, end;
	int nbThreadTest[NB_TEST] = {2,
								 3,
								 4};
	printf(" =========================================\n");
	printf(" +                Séquentiel             +\n");
	printf(" =========================================\n");
	start = omp_get_wtime();
	for (i = 0; i < DIM1; i++)
	{
		for (j = 0; j < DIM2; j++)
		{
			A[i][j] = i + 1;
			B[i][j] = j + 1;
		}
	}

	for (i = 0; i < DIM1; i++)
	{
		for (j = 0; j < DIM2; j++)
		{
			C[i][j] = cos((A[i][j] - B[i][j]) * (A[i][j] + B[i][j]) / B[i][j]);
		}
	}

	res = 0;
	for (i = 0; i < DIM1; i++)
	{
		for (j = 0; j < DIM2; j++)
		{
			res = res + C[i][j];
		}
	}
	end = omp_get_wtime();
	printf("res : %g \n", res);
	tmpSeq = (end - start);
	printf("temps d'execution séquentiel : %lg \n", tmpSeq);
	printf(" =========================================\n");
	printf(" +                Parralelle             +\n");
	printf(" =========================================\n");
	for (size_t nbThreads = 0; nbThreads < NB_TEST; nbThreads++)
	{
		res = 0;
		start = omp_get_wtime();
#pragma omp parallel for num_threads(nbThreadTest[nbThreads]), private(i, j), collapse(2)
		for (i = 0; i < DIM1; i++)
		{
			for (j = 0; j < DIM2; j++)
			{
				A[i][j] = i + 1;
				B[i][j] = j + 1;
			}
		}
#pragma omp parallel for num_threads(nbThreadTest[nbThreads]), private(i, j), collapse(2)
		for (i = 0; i < DIM1; i++)
		{
			for (j = 0; j < DIM2; j++)
			{
				C[i][j] = cos((A[i][j] - B[i][j]) * (A[i][j] + B[i][j]) / B[i][j]);
			}
		}

		res = 0;
		for (i = 0; i < DIM1; i++)
		{
			for (j = 0; j < DIM2; j++)
			{
				res = res + C[i][j];
			}
		}
		end = omp_get_wtime();
		tmpPar = (end - start);
		printf("res : %g \n", res);
		printf(" temps d'execution parrallel pour %d threads: %lg \n", nbThreadTest[nbThreads], tmpPar);
		acceleration = tmpSeq / tmpPar;
		printf(" acceleration pour %d threads = %lg\n", nbThreadTest[nbThreads], acceleration);
		efficacite = acceleration / nbThreadTest[nbThreads];
		printf(" efficacite pour %d threads = %lg\n", nbThreadTest[nbThreads], efficacite);
		printf("=========================================\n");
	}
}
