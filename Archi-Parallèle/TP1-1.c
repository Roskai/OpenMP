#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NBELEM 2200

int A[NBELEM][NBELEM], B[NBELEM][NBELEM], C[NBELEM][NBELEM];

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
	res = 0;

	start = omp_get_wtime();

	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			for (k = 0; k < NBELEM; k++)
			{
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}

	end = omp_get_wtime();

	tExe = (end - start);
	printf("temps : %g \n", tExe);

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
