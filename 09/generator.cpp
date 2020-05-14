#include <random>
#include <ctime>
#include <fstream>

int main()
{
	srand(time(NULL));
	std::ofstream outfile("file.txt");
	
	for(int i = 0; i < 1000; i++)
	{
		outfile << rand() << std::endl;
	}
	
	outfile.close();
	return 0;
}
