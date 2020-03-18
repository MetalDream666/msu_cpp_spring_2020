#ifndef MAKEALLOCATOR_H
#define MAKEALLOCATOR_H

#include <cstdlib>

typedef class Allocator
{
private:
	char* start = nullptr;
	char* current = nullptr;
	size_t max;
	size_t curNum;
	
public:
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	char* get_start();
	
} Allocator;

#endif
