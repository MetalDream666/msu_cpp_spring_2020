CC=g++
CFLAGS=-c -Wall

all: makeallocator

test: test.o makeallocator.o
	$(CC) makeallocator.o test.o -o test

makeallocator.o: makeallocator.cpp
	$(CC) $(CFLAGS) makeallocator.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

clean:
	rm -rf *.o test

