#include <iostream>
#include <cstdlib>

char* start = nullptr;
char* current = nullptr;
size_t max = 0;
size_t curNum;

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
		return (current - size);
	}
}

void reset()
{
	current = start;
}


int main()
{
	makeAllocator(1024);
	char* some1 = alloc(20);
	std::cout << some1 << std::endl;
	char* some2 = alloc(20);
	std::cout << some2 << std::endl;
	reset();
	char* some3 = alloc(30);
	std::cout << some3 << std::endl;
	reset();
	free(start);
}
