#ifndef MAKEALLOCATOR_H
#define MAKEALLOCATOR_H

#include <cstdlib>

extern char* start;
extern char* current;
extern size_t max;
extern size_t curNum;

void makeAllocator(size_t maxSize);

char* alloc(size_t size);

void reset();

#endif
