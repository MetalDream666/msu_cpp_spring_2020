#include <cstdio>
#include <cstdlib>

#include "makeallocator.h"

int main()
{
	makeAllocator(30);
	char* some1 = alloc(20);
	printf("%p\n", some1);
	char* some2 = alloc(20);
	printf("%p\n", some2);
	reset();
	char* some3 = alloc(30);
	printf("%p\n", some3);
	reset();
	free(start);
	return 0;
}
