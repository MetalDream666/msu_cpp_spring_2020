CPP=g++
CFLAGS=-c -Wall

all: test

test: test.o format.o
	$(CPP) format.o test.o -o test
	./test

format.o: format.cpp
	$(CPP) $(CFLAGS) format.cpp

test.o: test.cpp
	$(CPP) $(CFLAGS) test.cpp

clean:
	rm -rf *.o test


