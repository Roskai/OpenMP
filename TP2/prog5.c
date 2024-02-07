#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define VALINIT 1000000
#define NBTOURS 300
#define NUM_THREAD 4
#define NB_TEST 5

int main(void)
{
	unsigned int nombreNombrePremierTrouverSeq = 0;
	int ncores, div;
	long int i, j;
	int nbThreadTest[NB_TEST] = {2,
								 3,
								 4,
								 omp_get_num_procs(),
								 omp_get_num_procs() * 2};
	double tmpSeq, tmpPar, acceleration, efficacite;
	ncores = omp_get_num_procs();
	printf("%d coeurs disponibles\n", ncores);
	printf(" =========================================\n");
	printf(" +                Séquentiel             +\n");
	printf(" =========================================\n");
	double start, end;
	start = omp_get_wtime();
	for (i = VALINIT; i < VALINIT + NBTOURS; i++)
	{
		j = 2;
		div = 0;
		while (i % j != 0 && div == 0)
		{
			j++;
			if (j <= sqrt(i) + 1)
			{
				div = 1;
				nombreNombrePremierTrouverSeq++;
			}
		}
	}
	end = omp_get_wtime();
	tmpSeq = (end - start);
	printf("temps d'execution séquentiel : %lg \n", tmpSeq);
	printf("%d nombres premiers de trouvés \n", nombreNombrePremierTrouverSeq);
#if false
    printf(" =========================================\n");
    printf(" +                Parralelle             +\n");
    printf(" =========================================\n");
    for (size_t nbThreads = 0; nbThreads < NB_TEST; nbThreads++)
    {
        printf(" Avec %d threads:\n", nbThreadTest[nbThreads]);
        unsigned int nombreNombrePremierTrouverPar = 0;
        start = omp_get_wtime();
#pragma omp parallel for num_threads(nbThreadTest[nbThreads]), private(div, i, j), schedule(dynamic)
        for (i = VALINIT; i < VALINIT + NBTOURS; i++)
        {
            j = 2;
            div = 0;
            while (i % j != 0 && div == 0)
            {
                j++;
                if (j >= i)
                {
                    div = 1;
                    nombreNombrePremierTrouverPar++;
                }
            }
        }
        if (nombreNombrePremierTrouverPar != nombreNombrePremierTrouverSeq)
        {
            fprintf(stderr, "Nombre de nombre premier invalide : %d trouvé, pour %d attendu", nombreNombrePremierTrouverPar, nombreNombrePremierTrouverSeq);
            exit(EXIT_FAILURE);
        }
        end = omp_get_wtime();
        tmpPar = (end - start);
		printf("%d nombres premiers de trouvés \n", nombreNombrePremierTrouverPar);
        printf(" temps d'execution parrallel pour %d threads: %lg \n", nbThreadTest[nbThreads], tmpPar);
        acceleration = tmpSeq / tmpPar;
        printf(" acceleration pour %d threads = %lg\n", nbThreadTest[nbThreads], acceleration);
        efficacite = acceleration / nbThreadTest[nbThreads];
        printf(" efficacite pour %d threads = %lg\n", nbThreadTest[nbThreads], efficacite);
        printf("=========================================\n");
    }
#endif
	return 0;
}
