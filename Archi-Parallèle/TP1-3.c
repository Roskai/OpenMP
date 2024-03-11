#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NBELEM 2200

int A[NBELEM][NBELEM], B[NBELEM][NBELEM], C[NBELEM][NBELEM], transB[NBELEM][NBELEM], transA[NBELEM][NBELEM];

// initialisation des matrices initiales (valeur sans importance)
void init2D(int tab[NBELEM][NBELEM])
{
	int i, j;
	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			tab[i][j] = 1;
		}
	}
}

void transpose(int matI[NBELEM][NBELEM], int matO[NBELEM][NBELEM])
{
	int i, j;
	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			matO[i][j] = matI[j][i];
		}
	}
}

// mise à 0 de la matrice résultat
void raz2D(int tab[NBELEM][NBELEM])
{
	int i, j;
	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			tab[i][j] = 0;
		}
	}
}

int main(void)
{
	int i, j, k;
	long long res;
	double start, end, tExe;

	// debut du traitement
	init2D(A);
	init2D(B);
	raz2D(C);
	transpose(B, transB);
	res = 0;

	start = omp_get_wtime();

	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			int acc = 0;
			for (k = 0; k < NBELEM; k++)
			{
				acc += A[i][k] * transB[k][j];
			}
			C[i][j] = acc;
		}
	}

	end = omp_get_wtime();

	tExe = (end - start);
	printf("temps avec transposé de B: %g \n", tExe);
/* 
	// debut du traitement
	init2D(A);
	init2D(B);
	raz2D(C);
	transpose(A, transA);
	res = 0;

	start = omp_get_wtime();

	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			int acc = 0;
			for (k = 0; k < NBELEM; k++)
			{
				acc += transA[i][k] * B[k][j];
			}
			C[i][j] = acc;
		}
	}

	end = omp_get_wtime();

	tExe = (end - start);
	printf("temps avec transposé de A : %g \n", tExe);

	init2D(A);
	init2D(B);
	raz2D(C);
	transpose(A, transA);
	start = omp_get_wtime();
	for (k = 0; k < NBELEM; k++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			for (i = 0; i < NBELEM; i++)
			{
				C[i][j] = C[i][j] + transA[i][k] * B[k][j];
			}
		}
	}
	end = omp_get_wtime();
	tExe = (end - start);
	printf("temps pour le pire cas : %g \n", tExe); */

	start = omp_get_wtime();

	for (i = 0; i < NBELEM; i++)
	{
		for (k = 0; k < NBELEM; k++)
		{
			for (j = 0; j < NBELEM; j++)
			{
				int acc = 0;
				acc += A[i][k] * transB[k][j];
				C[i][j] = acc;
			}
		}
	}

	end = omp_get_wtime();

	tExe = (end - start);
	printf("temps pour le meilleurs cas : %g \n", tExe);
	// pour que les résultats soient utilisés
	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			res = res + C[i][j];
		}
	}

	printf("resultat : %I64lld \n", res);

	return 0;
}
