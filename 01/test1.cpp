#include <cstdlib>
#include <cstdio>

#include "makeallocator.h"

int main()
{
	const int ALLSIZE = 10000;
	
	makeAllocator(ALLSIZE);
	if(start == nullptr)
	{
		printf("Error allocating memory\n");
		return 3;
	}
	char* pointer;
	
	for(int i=1; i<ALLSIZE; i++)
	{
		for(int j=0; j<(ALLSIZE / i); j++)
		{
			pointer = alloc(i);
			if(pointer == nullptr)
			{
				printf("Something went wrong...\n");
				return 1;
			}
		}
		pointer = alloc(i);
		if(pointer != nullptr)
		{
			printf("It's too good...\n");
			return 2;
		}
		reset();
	}
	printf("Everything is OK!\n");
	return 0;
}
