#include <iostream>

#include "vector.h"


int main()
{
	MyVector<int> vec;
	
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	std::cout << vec[0] << vec[1] << std::endl;
	
	try
	{
		std::cout << vec[7] << std::endl;
	}
	catch(std::out_of_range& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << vec.size() << std::endl;
	std::cout << vec.pop_back() << std::endl;
	std::cout << vec.size() << std::endl;

	vec.resize(10, 2);
	std::cout << vec[9] << std::endl;
	
	for(auto it: vec)
	{
		std::cout << it;
	}
	
	for(auto& it: vec)
	{
		it = 6;
	}
	
	std::cout << std::endl;
	
	for(auto it: vec)
	{
		std::cout << it;
	}
	
	std::cout << std::endl;
	vec[1] = 3;
	std::cout << vec[1] << std::endl;
	
	return 0;
}
