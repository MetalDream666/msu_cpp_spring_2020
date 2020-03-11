#include <cstdlib>

#include "makeallocator.h"

char* start = nullptr;
char* current = nullptr;
size_t max = 0;
size_t curNum = 0;

void makeAllocator(size_t maxSize)
{
	max = maxSize;
	curNum = 0;
	start = (char*)malloc(maxSize);
	current = start;
}

char* alloc(size_t size)
{
	if(curNum + size > max)
	{
		return nullptr;
	}
	else
	{
		current += size;
		curNum += size;
		return (current - size);
	}
}

void reset()
{
	current = start;
	curNum = 0;
}

