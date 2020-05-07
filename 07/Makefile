CPP=g++
CFLAGS=-c -Wall

all: test

test: test.o
	$(CPP) test.o -o test
	./test

test.o: test.cpp
	$(CPP) $(CFLAGS) test.cpp

clean:
	rm -rf *.o test


