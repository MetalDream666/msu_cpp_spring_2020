CPP=g++
CFLAGS=-c -Wall

all: test

test: test.o bigint.o
	$(CPP) bigint.o test.o -o test
	./test

serializer.o: bigint.cpp
	$(CPP) $(CFLAGS) bigint.cpp

test.o: test.cpp
	$(CPP) $(CFLAGS) test.cpp

clean:
	rm -rf *.o test


