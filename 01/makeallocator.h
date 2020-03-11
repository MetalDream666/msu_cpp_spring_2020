#ifndef MAKEALLOCATOR_H
#define MAKEALLOCATOR_H

#include <cstdlib>

char* start = nullptr;
char* current = nullptr;
size_t max = 0;
size_t curNum = 0;

void makeAllocator(size_t maxSize);

char* alloc(size_t size);

void reset();

#endif
