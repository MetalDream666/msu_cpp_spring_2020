#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <sstream>
#include <stdexcept>


void process(std::stringstream& str, int counter);

template <class T, class... Args> void process(std::stringstream& str, int counter, T&& val, Args&&... args)
{
	if(counter == 0)
	{
		str << val;
	}
	else 
		process(str, counter - 1, std::forward<Args>(args)...);
}


template <class... ArgsT> std::string format(std::string s, ArgsT&&... args)
{
	std::stringstream str;
	bool opened = false;
	std::string num;
	
	for(auto i: s)
	{
		if(opened)
		{
			if(i == '{')
			{
				throw std::runtime_error("too many opening brackets");
			}
			if(i == '}')
			{
				process(str, stoi(num), std::forward<ArgsT>(args)...);
				opened = false;
				num = "";
				continue;
			}
			num += i;
			continue;
		}
		else
		{
			if(i == '{')
			{
				opened = true;
				continue;
			}
			if(i == '}')
			{
				throw std::runtime_error("closing bracket without been opened");
			}
			str << i;
		}
		
	}
	
	if(!(num.empty()))
	{
		throw std::runtime_error("lol");
	}
	
	return str.str();
}

#endif
