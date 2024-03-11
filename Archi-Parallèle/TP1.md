# Amélioration de programme de pour l'architecture d'un cœur

## Question préalable : l'ordre des boucles a-t-il un impact sur la justesse du résultat calculé ?

Non, l'odre des boucles n'a pas d'impact sur le resultat calculé.

## Évaluation des possibilités de l'odres des boucles.
Il y a 3! soit 1+2+3 soit 6 possibilités d'ordes de boucles différents.

## Resultat des tests dans TP1-2.c
> Nota : NBELEM vaut 2200

---
### boucle i j k 

temps : 46.9373 

---
### boucle i k j 

temps : **28.0746** 

---
### boucle j k i 

temps : 60.1253 

---
### boucle j i k 

temps : 30.3558 

---
### boucle k j i 

temps : 61.5234 

---
### boucle k i j 

temps : **28.1239**

---
### boucle k j i 

temps : 61.7377 

---

On remarque que les temps les plus courts sont lorsque la bloucle `j` est à la fin 

Il y a un écart d'environ 33 secondes entre le plus cours et le plus long.

## Utilisation d'une accumulation 
Avec la modification suivante dans le code
```c
	for (i = 0; i < NBELEM; i++)
	{
		for (j = 0; j < NBELEM; j++)
		{
			int acc = 0;
			for (k = 0; k < NBELEM; k++)
			{
				acc += +A[i][k] * B[k][j];
			}
			C[i][j] = acc;
		}
	}
```

Le temps d'éxécution est de le 28,71 secondes. ce qui est une amélioration de 58% vis a vis du temps de base.

## Réduction des défauts de cache mémoire par transposition

Au sein de la boucle portant sur K, les valeurs successives de `A[i][k]` sont sur la même la même colone. C'est a dire qu'on passe en revue les différentes case de la ligne. Cela est favorable pour la réduction des défauts de caches car celle-ci sont chargée.

Au sein de la boucle portant sur K, les valeurs successives de `B[k][j]` sont sur la même la même ligne. Cela est défavorable pour la réduction des défauts de caches car l'on doit chargé de nouvelle ligne a chaque itération.

Il est plus facile de parcourire une colone qu'une ligne car les valeur sont contigües en memoire car on parcours dans le même espace mémoire.



