# Compte rendu TP4

## Rapelle des valeurs

IT  | hypothèse 1| hypothèse 2 | hypothèse 3	
--- |--- | --- | --- 
ITA | 8 | 8  | 2
ITB | 8 | 4  | 5
ITC | 7 | 3  | 4
ITD | 2 | 7  | 7
ITE | 1 | 1  | 1

Le PAS vaut 200 tours de boucles
## Temps théorique en séquenciel

Pour chaque hypothèse nous avons un temps de `(PAS * ITA)³ + (PAS * ITB)³ + (PAS * ITC)³ + (PAS * ITD)³ + (PAS * IT5)³`.

Pour l'hypothèse 1 nous aurons un temps de 11 008 000 000 tours de boucle. 

Pour l'hypothèse 2 nous aurons un temps de 7 576 000 000 tours de boucle.

Pour l'hypothèse 3 nous aurons un temps de 2 584 000 000 tours de boucle.

## Graphe de dépendances
![Graphe de dépendance.](GrapheDepandance.png)

 ## Version parallèle V1
![](GrapheDependanceV1.png)
 Dans cette version, les calculs de A, B et C sont parallèlisés. Ce qui fait que le temps sera, pour l'hypothèse 1 `(PAS * ITA)³ + (PAS * ITD)³ + (PAS * IT5)³` ou ` (PAS * ITB)³ + (PAS * ITD)³ + (PAS * IT5)³` car A et B ont le même nombre de pas. Ce qui donne un temps de 4 168 000 000 tours de boucle. L'accélération est de 2,641 et l'efficacité de 0,88 (accélération/3)

 Pour l'hypothèse 2 : `(PAS * ITA)³ + (PAS * ITD)³ + (PAS * IT5)³` soit un temps de 6 848 000 000 tours de boucle. L'accélération est de 1,106 et l'efficacité de 0,37 (accélération/3)

 Pour l'hypothèse 3 : `(PAS * ITB)³ + (PAS * ITD)³ + (PAS * IT5)³` soit un temps de 2 008 000 000 tours de boucle. L'accélération est de 1,286 et l'efficacité de 0,43 (accélération/3)

## Version parallèle V2
![](GrapheDependanceV2.png)

Dans cette version, les calculs de A et B sont parallèlisés et C et D sont parallèlisés.
Ce qui fait que le temps sera, pour l'hypothèse 1 `(PAS * ITA)³ + (PAS * ITC)³ + (PAS * IT5)³`. Ce qui donne un temps de 6 848 000 000 tours de boucle. L'accélération est de 1.06 et l'efficacité de 0,53 (accélération/3)

 Pour l'hypothèse 2 : `(PAS * ITA)³ + (PAS * ITC)³ + (PAS * IT5)³` soit un temps de 6 848 000 000 tours de boucle. L'accélération est de 1,106 et l'efficacité de 0,37 (accélération/3)

 Pour l'hypothèse 3 : `(PAS * ITB)³ + (PAS * ITD)³ + (PAS * IT5)³` soit un temps de 2 008 000 000 tours de boucle. L'accélération est de 1,286 et l'efficacité de 0,43 (accélération/3)


