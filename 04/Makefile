CPP=g++
CFLAGS=-c -Wall

all: test

test: test.o serializer.o
	$(CPP) serializer.o test.o -o test
	./test

serializer.o: serializer.cpp
	$(CPP) $(CFLAGS) serializer.cpp

test.o: test.cpp
	$(CPP) $(CFLAGS) test.cpp

clean:
	rm -rf *.o test


