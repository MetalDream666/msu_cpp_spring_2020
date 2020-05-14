#include "sort_threads.h"

void right(uint64_t& written, bool& written_initialized, bool& written_max, bool& stop, std::mutex& written_lock, const std::string& infile_name, const std::string& right_filename)
{
	uint64_t pred_max;
	uint64_t max;
	int count_max;
	uint64_t num;
	std::ifstream infile(infile_name);
	std::ofstream outfile(right_filename);
	bool first_turn(true);
	count_max = 0;
	max = 0;
	
	while(true)
	{
		infile.clear();
		infile.seekg(0, std::ios::beg);

		if(first_turn)
		{
			while(infile >> num)
			{
				if(num > max)
				{
					max = num;
					count_max = 1;
				}
				else if(num == max)
				{
					count_max++;
				}
			}
			first_turn = false;
		}
		else
		{
			count_max = 0;
			pred_max = max;
			max = 0;
			while(infile >> num)
			{
				if((num > max) && (num < pred_max))
				{
					max = num;
					count_max = 1;
				}
				else if(num == max)
				{
					count_max++;
				}
			}
		}
	
		{
			std::unique_lock<std::mutex> wguard(written_lock);
			if (stop)
			{
				break;
			}
			if (!written_initialized)
			{
				written_initialized = true;
				written = max;
				written_max = true;
			}
			else
			{
				if ((written >= max) && (!written_max))
				{
				//	std::cout << "max:" << max << " written:" << written << " written_max:" << written_max << std::endl;
				//	std::cout << "(written >= max) && (!written_max)" << std::endl;
					stop = true;
					break;
				}
				else
				{
					written_max = true;
					written = max;
				}
			}
		}
		
		for(int i = 0; i < count_max; i++)
		{
			outfile << max << std::endl;
		}
	}
	
	infile.close();
	outfile.close();
}

void left(uint64_t& written, bool& written_initialized, bool& written_max, bool& stop, std::mutex& written_lock, const std::string& infile_name, const std::string& left_filename)
{
	uint64_t pred_min;
	uint64_t min;
	uint64_t num;
	int count_min;
	std::ifstream infile(infile_name);
	std::ofstream outfile(left_filename);
	bool first_turn(true);
	
	count_min = 0;
	min = std::numeric_limits<uint64_t>::max();
	
	while(true)
	{
		infile.clear();
		infile.seekg(0, std::ios::beg);
		if(first_turn)
		{
			while(infile >> num)
			{
				if(num < min)
				{
					min = num;
					count_min = 1;
				}
				else if(num == min)
				{
					count_min++;
				}
			}
			first_turn = false;
		}
		else
		{
			pred_min = min;
			count_min = 0;
			min = std::numeric_limits<uint64_t>::max();
			while(infile >> num)
			{
				if((num < min) && (num > pred_min))
				{
					min = num;
					count_min = 1;
				}
				else if(num == min)
				{
					count_min++;
				}
			}
		}
	
		{
			std::unique_lock<std::mutex> wguard(written_lock);
			if(stop)
			{
				break;
			}
			if (!written_initialized)
			{
				written_initialized = true;
				written_max = false;
				written = min;
			}
			else
			{
				if ((written <= min) && written_max)
				{
				//	std::cout << "min:" << min << " written:" << written << " written_max:" << written_max << std::endl;
				//	std::cout << "(written <= min) && written_max" << std::endl;
					stop = true;
					break;
				}
				else
				{
					written_max = false;
					written = min;
				}
			}
		}
		
		for(int i = 0; i < count_min; i++)
		{
			outfile << min << std::endl;
		}
	}
	
	infile.close();
	outfile.close();
}

