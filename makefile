CC = gcc 
CFLAGS = -Wall -fopenmp -lm 

all:prog8

clean:
	rm -vf *.out 
	rm -vf *.o

##############
# TP OPEN-MP #
##############
prog8:
	$(CC) $(CFLAGS) -DHYPOTHESE=$(HYPOTHESE) $(PWD)/TP4/$@.c -o $@.out
