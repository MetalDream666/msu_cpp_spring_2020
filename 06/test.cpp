#include <iostream>
#include <cassert>

#include "format.h"

int main()
{
	auto text = format("{1}+{1} = {0}", 2, "one");
	assert(text == "one+one = 2");
	std::cout << text << std::endl;
    return 0;
}
