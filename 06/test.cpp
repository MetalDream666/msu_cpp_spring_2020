#include <iostream>
#include <cassert>

#include "format.h"

int main()
{
	auto text = format("{1}+{1} = {0}", 2, "one");
	assert(text == "one+one = 2");
	std::cout << text << std::endl;
	try
	{
		auto text1 = format("{2}", 55);
	}
	catch(std::runtime_error& ex)
	{
		std::cout << "runtime error catched" << std::endl;
		std::cout << ex.what() << std::endl;
	}
    return 0;
}
