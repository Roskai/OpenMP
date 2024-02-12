# Compte rendu TP4

## Temps théorique en séquenciel

Pour chaque hypothèse nous avons un temps de `(PAS * ITA)³ + (PAS * ITB)³ + (PAS * ITC)³ + (PAS * ITD)³ + (PAS * IT5)³`.

Pour l'hypothèse 1 nous aurons un temps de 11 008 000 000 tours de boucle. 

Pour l'hypothèse 2 nous aurons un temps de 7 576 000 000 tours de boucle.

Pour l'hypothèse 3 nous aurons un temps de 2 584 000 000 tours de boucle.

## Graphe de dépendances
 `À FAIRE`

 ## Version parallèle V1

 Dans cette version, les calculs de A, B et C sont parallèlisés. Ce qui fait que le temps sera, pour l'hypothèse 1 `(PAS * ITA)³ + (PAS * ITD)³ + (PAS * IT5)³` ou ` (PAS * ITB)³ + (PAS * ITD)³ + (PAS * IT5)³` car A et B ont le même nombre de pas. Ce qui donne un temps de 4 168 000 000 tours de boucle. L'accélération est de 2,641 et l'efficacité de 0,880 (accélération/3)

 Pour l'hypothèse 2 : `(PAS * ITA)³ + (PAS * ITD)³ + (PAS * IT5)³` soit un temps de 6 848 000 000 tours de boucle. L'accélération est de 1,106 et l'efficacité de 0,369 (accélération/3)



 Pour l'hypothèse 3 : `(PAS * ITB)³ + (PAS * ITD)³ + (PAS * IT5)³` soit un temps de 2 008 000 000 tours de boucle. L'accélération est de 1,286 et l'efficacité de 0,428 (accélération/3)

