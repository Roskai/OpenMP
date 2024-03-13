#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define PAS 200
#define NBELEM 2000

// Si HYPOTHESE n'est pas défini lors de la compilation, utilisation de l'Hypothèse 1 par défaut
#ifndef HYPOTHESE
#define HYPOTHESE 1
#warning "Aucune valeur pour HYPOTHESE fournie, utilisation de la valeur par défaut 1"
#endif

// Définir les valeurs IT en fonction de l'hypothèse choisie
#if HYPOTHESE == 1
#define ITA 8
#define ITB 8
#define ITC 7
#define ITD 2
#define ITE 1
#elif HYPOTHESE == 2
#define ITA 8
#define ITB 4
#define ITC 3
#define ITD 7
#define ITE 1
#elif HYPOTHESE == 3
#define ITA 2
#define ITB 5
#define ITC 4
#define ITD 7
#define ITE 1
#else
#error "Valeur invalide pour HYPOTHESE, veuillez choisir entre 1, 2 ou 3"
#endif

int M1[NBELEM][NBELEM], M2[NBELEM][NBELEM], M3[NBELEM][NBELEM], M4[NBELEM][NBELEM], M5[NBELEM][NBELEM], M6[NBELEM][NBELEM];

int A[NBELEM][NBELEM], B[NBELEM][NBELEM], C[NBELEM][NBELEM], D[NBELEM][NBELEM], E[NBELEM][NBELEM];

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
	int ncores;
	int i, j, k;
	long long resGOLD, res;
	double start, end, tempsSeq, tempsv1, tempsV2, tempsV3;
	double accelerationV1, accelerationV2, accelerationV3;
	double efficaciteV1, efficaciteV2, efficaciteV3;
	ncores = omp_get_num_procs();
	printf("%d coeurs disponibles\n", ncores);

	// version séquentielle

	init2D(M1);
	init2D(M2);
	init2D(M3);
	init2D(M4);
	init2D(M5);
	init2D(M6);

	raz2D(A);
	raz2D(B);
	raz2D(C);
	raz2D(D);
	raz2D(E);

	printf("*******************************************\n");
	printf("Version séquentiel \n");
	printf("*******************************************\n");
	start = omp_get_wtime();

	// traitement A
	for (i = 0; i < PAS * ITA; i++)
	{
		for (j = 0; j < PAS * ITA; j++)
		{
			for (k = 0; k < PAS * ITA; k++)
			{
				A[i][j] = A[i][j] + M1[i][k] * M2[k][j];
			}
		}
	}

	// traitement B
	for (i = 0; i < PAS * ITB; i++)
	{
		for (j = 0; j < PAS * ITB; j++)
		{
			for (k = 0; k < PAS * ITB; k++)
			{
				B[i][j] = B[i][j] + M3[i][k] * M4[k][j];
			}
		}
	}

	// traitement C
	for (i = 0; i < PAS * ITC; i++)
	{
		for (j = 0; j < PAS * ITC; j++)
		{
			for (k = 0; k < PAS * ITC; k++)
			{
				C[i][j] = C[i][j] + M5[i][k] * M6[k][j];
			}
		}
	}

	// traitement D
	for (i = 0; i < PAS * ITD; i++)
	{
		for (j = 0; j < PAS * ITD; j++)
		{
			for (k = 0; k < PAS * ITD; k++)
			{
				D[i][j] = D[i][j] + A[i][k] * B[k][j];
			}
		}
	}

	// traitement E
	for (i = 0; i < PAS * ITE; i++)
	{
		for (j = 0; j < PAS * ITE; j++)
		{
			for (k = 0; k < PAS * ITE; k++)
			{
				E[i][j] = E[i][j] + D[i][k] * C[k][j];
			}
		}
	}

	end = omp_get_wtime();
	resGOLD = 0;
	tempsSeq = (end - start);
	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			resGOLD = resGOLD + E[i][j];
		}
	}
	printf("temps en sequentiel : %g \n", tempsSeq);

	printf("*******************************************\n");
	printf("Version paralèlle 1 \n");
	printf("*******************************************\n");

	raz2D(A);
	raz2D(B);
	raz2D(C);
	raz2D(D);
	raz2D(E);

	start = omp_get_wtime();

#pragma omp parallel sections private(i, j, k)
	{
#pragma omp section
		{

			for (i = 0; i < PAS * ITA; i++)
			{
				for (j = 0; j < PAS * ITA; j++)
				{
					for (k = 0; k < PAS * ITA; k++)
					{
						A[i][j] = A[i][j] + M1[i][k] * M2[k][j];
					}
				}
			}
		}
#pragma omp section
		{
			for (i = 0; i < PAS * ITB; i++)
			{
				for (j = 0; j < PAS * ITB; j++)
				{
					for (k = 0; k < PAS * ITB; k++)
					{
						B[i][j] = B[i][j] + M3[i][k] * M4[k][j];
					}
				}
			}
		}
#pragma omp section
		{
			for (i = 0; i < PAS * ITC; i++)
			{
				for (j = 0; j < PAS * ITC; j++)
				{
					for (k = 0; k < PAS * ITC; k++)
					{
						C[i][j] = C[i][j] + M5[i][k] * M6[k][j];
					}
				}
			}
		}
	}
	// traitement D
	for (i = 0; i < PAS * ITD; i++)
	{
		for (j = 0; j < PAS * ITD; j++)
		{
			for (k = 0; k < PAS * ITD; k++)
			{
				D[i][j] = D[i][j] + A[i][k] * B[k][j];
			}
		}
	}

	// traitement E
	for (i = 0; i < PAS * ITE; i++)
	{
		for (j = 0; j < PAS * ITE; j++)
		{
			for (k = 0; k < PAS * ITE; k++)
			{
				E[i][j] = E[i][j] + D[i][k] * C[k][j];
			}
		}
	}

	end = omp_get_wtime();
	res = 0;
	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			res = res + E[i][j];
		}
	}
	if (res != resGOLD)
	{
		perror("V1 : le resultat obtenu lors des traitement de la version diffère de la valeur trouvé en séquentiel.");
		exit(EXIT_FAILURE);
	}

	tempsv1 = (end - start);
	printf("temps pour la version 1 : %g \n", tempsv1);

	printf("*******************************************\n");
	printf("Version paralèlle 2 \n");
	printf("*******************************************\n");

	raz2D(A);
	raz2D(B);
	raz2D(C);
	raz2D(D);
	raz2D(E);

	start = omp_get_wtime();

#pragma omp parallel sections private(i, j, k)
	{
#pragma omp section
		{

			for (i = 0; i < PAS * ITA; i++)

				for (j = 0; j < PAS * ITA; j++)

					for (k = 0; k < PAS * ITA; k++)

						A[i][j] = A[i][j] + M1[i][k] * M2[k][j];
}

#pragma omp section
{
	for (i = 0; i < PAS * ITB; i++)

		for (j = 0; j < PAS * ITB; j++)

			for (k = 0; k < PAS * ITB; k++)

				B[i][j] = B[i][j] + M3[i][k] * M4[k][j];
}
}
#pragma omp parallel sections private(i, j, k)
{
#pragma omp section
	{
		for (i = 0; i < PAS * ITC; i++)
		{
			for (j = 0; j < PAS * ITC; j++)
			{
				for (k = 0; k < PAS * ITC; k++)
				{
					C[i][j] = C[i][j] + M5[i][k] * M6[k][j];
				}
			}
		}
	}
#pragma omp section
	{
		// traitement D
		for (i = 0; i < PAS * ITD; i++)
		{
			for (j = 0; j < PAS * ITD; j++)
			{
				for (k = 0; k < PAS * ITD; k++)
				{
					D[i][j] = D[i][j] + A[i][k] * B[k][j];
				}
			}
		}
	}
}
// traitement E
for (i = 0; i < PAS * ITE; i++)
{
	for (j = 0; j < PAS * ITE; j++)
	{
		for (k = 0; k < PAS * ITE; k++)
		{
			E[i][j] = E[i][j] + D[i][k] * C[k][j];
		}
	}
}

end = omp_get_wtime();
res = 0;
for (i = 0; i < NBELEM; i++)
{
	for (j = 0; j < NBELEM; j++)
	{
		res = res + E[i][j];
	}
}
if (res != resGOLD)
{
	perror("V2 : le resultat obtenu lors des traitement de la version diffère de la valeur trouvé en séquentiel.");
	exit(EXIT_FAILURE);
}
tempsV2 = (end - start);
printf("temps pour la version 2 : %g \n", tempsV2);

printf("*******************************************\n");
printf("Version paralèlle 3 \n");
printf("*******************************************\n");

raz2D(A);
raz2D(B);
raz2D(C);
raz2D(D);
raz2D(E);

omp_set_nested(1);
start = omp_get_wtime();
omp_set_num_threads(3);
#pragma omp parallel sections private(i, j, k)
{
#pragma omp parallel sections private(i, j, k)
	{
#pragma omp section
		{for (i = 0; i < PAS * ITA; i++)

			 for (j = 0; j < PAS * ITA; j++)

				 for (k = 0; k < PAS * ITA; k++)
					 A[i][j] = A[i][j] + M1[i][k] * M2[k][j];
}
#pragma omp section
{
	for (i = 0; i < PAS * ITB; i++)

		for (j = 0; j < PAS * ITB; j++)

			for (k = 0; k < PAS * ITB; k++)

				B[i][j] = B[i][j] + M3[i][k] * M4[k][j];
}
}
#pragma omp section
{
	for (i = 0; i < PAS * ITC; i++)

		for (j = 0; j < PAS * ITC; j++)

			for (k = 0; k < PAS * ITC; k++)

				C[i][j] = C[i][j] + M5[i][k] * M6[k][j];
}
}

// traitement D
for (i = 0; i < PAS * ITD; i++)
{
	for (j = 0; j < PAS * ITD; j++)
	{
		for (k = 0; k < PAS * ITD; k++)
		{
			D[i][j] = D[i][j] + A[i][k] * B[k][j];
		}
	}
}

// traitement E
for (i = 0; i < PAS * ITE; i++)
{
	for (j = 0; j < PAS * ITE; j++)
	{
		for (k = 0; k < PAS * ITE; k++)
		{
			E[i][j] = E[i][j] + D[i][k] * C[k][j];
		}
	}
}

end = omp_get_wtime();

tempsV3 = (end - start);
printf("temps pour la version 3 : %g \n", tempsV3);

res = 0;
for (i = 0; i < NBELEM; i++)
{
	for (j = 0; j < NBELEM; j++)
	{
		res = res + E[i][j];
	}
}
if (res != resGOLD)
{
	perror("V3 : le resultat obtenu lors des traitement de la version diffère de la valeur trouvé en séquentiel.");
	exit(EXIT_FAILURE);
}
// acceleration = tmpSeq / tmpPar;
// efficacite = acceleration / nbThreadTest[nbThreads];
accelerationV1 = tempsSeq / tempsv1;
efficaciteV1 = accelerationV1 / ncores;

accelerationV2 = tempsSeq / tempsV2;
efficaciteV2 = accelerationV2 / ncores;

accelerationV3 = tempsSeq / tempsV3;
efficaciteV3 = accelerationV3 / 3;

printf("===========================================\n");
printf("accelerationV1 = %g | efficacité V1 = %g \n", accelerationV1, efficaciteV1);
printf("accelerationV2 = %g | efficacité V2 = %g \n", accelerationV2, efficaciteV2);
printf("accelerationV3 = %g | efficacité V3 = %g (pour 3 threads)\n", accelerationV3, efficaciteV3);

printf("resultat : %I64lld \n", res);

return 0;
}
