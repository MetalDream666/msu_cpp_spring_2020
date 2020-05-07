#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>


void get_string_args(std::vector<std::string>& words);

template <class T, class... ArgsT> void get_string_args(std::vector<std::string>& words, T&& val, ArgsT&&... args)
{
	std::stringstream s;
	s << val;
	words.push_back(s.str());
	
	get_string_args(words, std::forward<ArgsT>(args)...);
}

template <class... ArgsT> std::string format(std::string s, ArgsT&&... args)
{
	std::stringstream str;
	bool opened = false;
	std::string num;
	
	std::vector<std::string> words;
	get_string_args(words, std::forward<ArgsT>(args)...);
	
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
				if(words.size() < (size_t)stoi(num))
				{
					throw std::runtime_error("not enougth arguments");
				}
				str << words[stoi(num)];
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
