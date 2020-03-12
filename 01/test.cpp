#include <cstdlib>
#include <cstdio>

#include "makeallocator.h"

int main()
{
	const int ALLSIZE = 1000000000000;
	
	Allocator all;
	
	all.makeAllocator(ALLSIZE);
	if(all.get_start() == nullptr)
	{
		printf("Error allocating memory\n");
		return 3;
	}
	printf("%p\n", all.get_start());
	char* pointer;
	
	for(int i=1; i<ALLSIZE; i++)
	{
		for(int j=0; j<(ALLSIZE / i); j++)
		{
			pointer = all.alloc(i);
			if(pointer == nullptr)
			{
				printf("Something went wrong...\n");
				return 1;
			}
		}
		pointer = all.alloc(i);
		if(pointer != nullptr)
		{
			printf("It's too good...\n");
			return 2;
		}
		all.reset();
	}
	printf("Everything is OK!\n");
	return 0;
}
