BDIR =$(PWD)
CC = gcc 
CFLAGS = -Wall -fopenmp -lm 

	
clean:
	rm -vf *.out 
	rm -vf *.o

prog1: 
	$(CC) $(CFLAGS) $(PWD)/TP1/$@.c -o $@.out 

prog2: prog2.c
	$(CC) $(CFLAGS)  $(PWD)/TP1/$@.c -o $@.out 

prog3: 
	$(CC) $(CFLAGS) $(PWD)/TP2/$@.c -o $@.out 

prog4: 
	$(CC) $(CFLAGS) $(PWD)/TP2/$@.c -o $@.out 
