CC = gcc 
CFLAGS = -Wall -fopenmp -lm 

	
clean:
	rm -vf *.out 
	rm -vf *.o

##############
# TP OPEN-MP #
##############
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

prog8: 
	$(CC) $(PWD)/TP4/$@.c -o $@.out $(CFLAGS)

prog8V1: 
	$(CC) $(PWD)/TP4/$@.c -o $@.out $(CFLAGS)

prog8V2: 
	$(CC) $(PWD)/TP4/$@.c -o $@.out $(CFLAGS)

TP1-1:
	$(CC) $(PWD)/Archi-Parallèle/$@.c -o $@.out $(CFLAGS)

TP1-2:
	$(CC) $(PWD)/Archi-Parallèle/$@.c -o $@.out $(CFLAGS)

TP1-3:
	$(CC) $(PWD)/Archi-Parallèle/$@.c -o $@.out $(CFLAGS)
