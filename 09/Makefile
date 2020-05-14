CPP=g++
CFLAGS=-c -Wall -pthread -std=c++14

all: test

test: test.o sort_threads.o create_test_file
	$(CPP) -pthread sort_threads.o test.o -o test
	./test

sort_threads.o: sort_threads.cpp
	$(CPP) $(CFLAGS) sort_threads.cpp

test.o: test.cpp
	$(CPP) $(CFLAGS) test.cpp

create_test_file: generator
	./generator

generator: generator.o
	$(CPP) generator.o -o generator

generator.o: generator.cpp
	$(CPP) -c -Wall generator.cpp

clean:
	rm -rf *.o test generator *.txt
