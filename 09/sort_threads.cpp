#include "sort_threads.h"

void Sorter::sort(const std::string& infile_name, const std::string& outfile_name)
{	
	auto right_thread = std::thread(&Sorter::right, this, std::ref(infile_name));
	auto left_thread = std::thread(&Sorter::left, this, std::ref(infile_name));
	
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
		
	return;
}

void Sorter::right(const std::string& infile_name)
{
	uint64_t pred_max;
	uint64_t max;
	int count_max;
	uint64_t num;
	std::ifstream infile(infile_name, std::ios::binary);
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
			while(!infile.eof())
			{
				infile.read(reinterpret_cast<char *>(&num), sizeof(num));
	//			std::cout << "right " << num << std::endl;
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
			while(!infile.eof())
			{
				infile.read(reinterpret_cast<char *>(&num), sizeof(num));
	//			std::cout << "right " << num << std::endl;
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

void Sorter::left(const std::string& infile_name)
{
	uint64_t pred_min;
	uint64_t min;
	uint64_t num;
	int count_min;
	std::ifstream infile(infile_name, std::ios::binary);
	std::ofstream outfile(left_filename);
	bool first_turn(true);
	
	count_min = 0;
	min = std::numeric_limits<uint64_t>::max();
//	char buf[8];
	
	while(true)
	{
		infile.clear();
		infile.seekg(0, std::ios::beg);
		if(first_turn)
		{
			while(!infile.eof())
			{
				infile.read(reinterpret_cast<char *>(&num), sizeof(num));
	//			std::cout << "left " << num << std::endl;
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
			while(!infile.eof())
			{
				infile.read(reinterpret_cast<char *>(&num), sizeof(num));
	//			std::cout << "left " << num << std::endl;
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

