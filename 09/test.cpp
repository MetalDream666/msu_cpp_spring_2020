#include <cstdlib>
#include <iostream>
#include <thread>
#include <fstream>
#include <atomic>
#include <mutex>
#include <limits>
#include <string>

#include "sort_threads.h"


int main()
{
	Sorter sorter;
	
	sorter.sort("file.txt", "answer.txt");
	
	std::cout << "The sorted numbers are in answer.txt" << std::endl;	
	
	return 0;
}
