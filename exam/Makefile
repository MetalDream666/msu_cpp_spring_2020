CC=g++
CFLAGS=-c -Wall 

all: test

test: eks.o
	$(CC) -pthread eks.o -o test

eks.o: eks.cpp
	$(CC) $(CFLAGS) eks.cpp

clean:
	rm -rf *.o test

