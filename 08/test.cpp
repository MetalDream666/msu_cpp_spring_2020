#include <iostream>

#include "threadpool.h"


struct A
{
};

void foo(const A&)
{
	std::cout << "foo" << std::endl;
}

int main()
{
	ThreadPool pool(4);

	auto task1 = pool.exec(foo, A());
	task1.get();
	

	auto task2 = pool.exec([](){ std::cout << "fackin lambda" << std::endl; return 1; });
	task2.get();

	return 0;
}
