#include <cstdlib>

#include "makeallocator.h"

void Allocator::makeAllocator(size_t maxSize)
{
	if(maxSize < 0)
	{
		return;
	}
	this -> start = (char*)malloc(maxSize);
	if(this -> start != nullptr)
	{
		this -> max = maxSize;
	}
	this -> curNum = 0;
	this -> current = start;
}

char* Allocator::alloc(size_t size)
{
	if(curNum + size > max)
	{
		return nullptr;
	}
	else
	{
		this -> current += size;
		this -> curNum += size;
		return (this -> current - size);
	}
}

void Allocator::reset()
{
	this -> current = start;
	this -> curNum = 0;
}

char* Allocator:: get_start()
{
	return this -> start;
}
