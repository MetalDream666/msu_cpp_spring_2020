#include <iostream>

#include "bigint.h"

int main()
{
    Bigint a = -9;
    std::cout << a << std::endl;
    Bigint b = 2;
    std::cout << b << std::endl;
    Bigint c = a + b;
    Bigint d = 0;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    if(c > a)
		std::cout << "true" << std::endl;
	if(!(c > b))
		std::cout << "false" << std::endl;
    std::cout << (b + a) << std::endl;
    if(c == (b + a))
		std::cout << "true" << std::endl;
	if(!(c < (b + a)))
		std::cout << "false" << std::endl;
    std::cout << (b - 0) << std::endl;

    return 0;
}
