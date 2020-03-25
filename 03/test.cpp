#include <iostream>
#include <cassert>

#include "matrix.h"

using namespace std;

int main()
{
	const size_t rows = 5;
	const size_t cols = 3;

	Matrix m(rows, cols);

	assert(m.getRows() == 5);
	assert(m.getColumns() == 3);

	m[1][2] = 5;
	cout << m[1][2] << endl;

	for(size_t i = 0; i < m.getRows()*m.getColumns(); i++)
	{
		m[i/cols][i%cols] = (int)(i);
	}
		
	m *= 3;
	for(size_t i = 0; i < m.getRows()*m.getColumns(); i++)
	{
		assert(m[i/cols][i%cols] == (int)(i*3));
	}

	Matrix m1(rows, cols);

	if (m1 == m)
	{
		cout << "Eq" << endl;
	}
	else
	{
		cout << "Neq" << endl;
	}
	
	try
	{
		cout << m[6][6] << endl;
	}
	catch(out_of_range& e)
	{
		cout << e.what() << endl;
	};
	
	return 0;
}
