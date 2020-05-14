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

enum Status 
{
	OK,
	WRITE_AND_STOP,
	JUST_DIE,
};


void right(uint64_t& written, bool& written_initialized, bool& written_max, bool& stop, std::mutex& written_lock, const std::string& infile_name, const std::string& left_filename);
void left(uint64_t& written, bool& written_initialized, bool& written_max, bool& stop, std::mutex& written_lock, const std::string& infile_name, const std::string& left_filename);


#endif
