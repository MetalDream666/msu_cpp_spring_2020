#ifndef SORT_THREADS_H
#define SORT_THREADS_H


#include <cstdlib>
#include <iostream>
#include <thread>
#include <fstream>
#include <atomic>
#include <mutex>
#include <limits>
#include <string>

class Sorter{
public: 
	Sorter() {}
	
	void sort(const std::string& infile_name, const std::string& outfile_name);
	
	~Sorter() {}

private:
	
	const std::string right_filename = "/tmp/right.txt";
	const std::string left_filename = "/tmp/left.txt";
	
	uint64_t written;
	bool written_initialized;
	bool written_max;
	bool stop = false;
	std::mutex written_lock;
	
	void right(const std::string& infile_name = "file.txt");
	void left(const std::string& infile_name = "file.txt");
};

#endif
