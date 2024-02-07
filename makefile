BDIR =$(PWD)
CC = gcc 
CFLAGS = -Wall -fopenmp -lm 

	
clean:
	rm -vf *.out 
	rm -vf *.o

prog1: 
	$(CC) $(PWD)/TP1/$@.c -o $@.out $(CFLAGS) 

prog2: 
	$(CC) $(PWD)/TP1/$@.c -o $@.out $(CFLAGS) 

prog3: 
	$(CC) $(PWD)/TP2/$@.c -o $@.out $(CFLAGS) 

prog4: 
	$(CC) $(PWD)/TP2/$@.c -o $@.out $(CFLAGS) 

prog5: 
	$(CC) $(PWD)/TP2/$@.c -o $@.out $(CFLAGS) 

prog6: 
	$(CC) $(PWD)/TP3/$@.c -o $@.out $(CFLAGS)

prog7: 
	$(CC) $(PWD)/TP3/$@.c -o $@.out $(CFLAGS)