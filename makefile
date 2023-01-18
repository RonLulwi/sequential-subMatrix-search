# 'make', 'make all'

CC = gcc
CFLAGS  = -Wall
LDFLAGS = -lm

all: main 

main:  main.o generalFunctions.o submatrixSearch.o
	$(CC) $(CFLAGS) -o main main.o generalFunctions.o submatrixSearch.o $(LDFLAGS)

main.o:  main.c generalFunctions.h 
	$(CC) $(CFLAGS) -c main.c $(LDFLAGS)	

generalFunctions.o:  generalFunctions.c generalFunctions.h 
	$(CC) $(CFLAGS) -c generalFunctions.c $(LDFLAGS)
	
submatrixSearch.o:  submatrixSearch.c submatrixSearch.h 
	$(CC) $(CFLAGS) -c submatrixSearch.c $(LDFLAGS)

clean: 
	rm -f main *.o


