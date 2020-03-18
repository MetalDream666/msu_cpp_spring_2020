CPP=g++
CFLAGS=-c -Wall

all: test

test: parser_prog.o parser.o
	$(CPP) parser.o parser_prog.o -o test
	./test

parser.o: parser.cpp
	$(CPP) $(CFLAGS) parser.cpp

parser_prog.o: parser_prog.cpp
	$(CPP) $(CFLAGS) parser_prog.cpp

clean:
	rm -rf *.o test

