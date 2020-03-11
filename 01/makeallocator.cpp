#include <cstdlib>

#include "makeallocator.h"

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
