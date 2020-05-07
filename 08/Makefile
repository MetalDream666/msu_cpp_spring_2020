CPP=g++
CFLAGS=-c -Wall -std=c++14

all: test

test: test.o threadpool.o
	$(CPP) -pthread threadpool.o test.o -o test
	./test

threadpool.o: threadpool.cpp
	$(CPP) $(CFLAGS) threadpool.cpp

test.o: test.cpp
	$(CPP) $(CFLAGS) test.cpp

clean:
	rm -rf *.o test
