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
    std::cout << (c > a) << std::endl;
    std::cout << (c > b) << std::endl;
    std::cout << (b + a) << std::endl;
    std::cout << (c == (b + a)) << std::endl;
    std::cout << (c < (b + a)) << std::endl;
    std::cout << (b + 0) << std::endl;

    return 0;
}
