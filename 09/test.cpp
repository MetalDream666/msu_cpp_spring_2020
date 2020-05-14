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
	uint64_t written;
	bool written_initialized;
	bool written_max;
	bool stop(false);
	std::mutex written_lock;
	
	const std::string right_filename = "right.txt";
	const std::string left_filename = "left.txt";
	const std::string infile_name = "file.txt";
	const std::string outfile_name = "answer.txt";
		
	auto right_thread = std::thread(right, std::ref(written), std::ref(written_initialized), std::ref(written_max), std::ref(stop), std::ref(written_lock), std::ref(infile_name), std::ref(right_filename));
	auto left_thread = std::thread(left, std::ref(written), std::ref(written_initialized), std::ref(written_max), std::ref(stop), std::ref(written_lock), std::ref(infile_name), std::ref(left_filename));
	  
	right_thread.join();
	left_thread.join();
	
	int num;
	std::ofstream outfile(outfile_name);
	std::ifstream left_file(left_filename);
	std::ifstream right_file(right_filename);
	
	while(left_file >> num)
	{
		outfile << num << std::endl;
	}
		
	char ch;
	size_t pos;
	if (!(right_file.peek() == std::ifstream::traits_type::eof()))
	{
		right_file.seekg(-1, std::ios::end);
		pos = right_file.tellg();
	//	std::cout << pos << std::endl;
		
		std::string line;
		for(size_t i = 0; i <= pos; i++)
		{
			ch = right_file.get();
			if(ch != '\n')
			{
				line.insert(line.begin(), ch);
			}
			else
			{
				if (line == "")
				{
					right_file.seekg(-2, std::ios::cur);
					continue;
				}
				outfile << line << std::endl;
				line.clear();
			}
			right_file.seekg(-2, std::ios::cur);
		}
		outfile << line << std::endl;
	}
	
	right_file.close();
	outfile.close();
	
	std::remove(left_filename.c_str());
	std::remove(right_filename.c_str());
	
	std::cout << "The sorted numbers are in answer.txt" << std::endl;	
	
	return 0;
}
