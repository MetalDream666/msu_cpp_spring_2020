#include <random>
#include <ctime>
#include <fstream>
#include <string>

int main()
{
	srand(time(NULL));
	std::ofstream outfile("file.bin", std::ios::binary);
	
	for(int i = 0; i < 1000; i++)
	{
		uint64_t num = (uint64_t)rand();
		outfile.write(reinterpret_cast<const char *>(&num), sizeof(num));
	}
	
	outfile.close();
	return 0;
}
