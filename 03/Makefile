CPP=g++
CFLAGS=-c -Wall

all: test

test: test.o matrix.o
	$(CPP) matrix.o test.o -o test
	./test

matrix.o: matrix.cpp
	$(CPP) $(CFLAGS) matrix.cpp
	
test.o: test.cpp
	$(CPP) $(CFLAGS) test.cpp

clean:
	rm -rf *.o test

