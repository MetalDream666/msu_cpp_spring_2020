#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>

class Matrix
{
private:
	const size_t rows = 0;
	const size_t cols = 0;
	
	int* matr = nullptr;

public:

	class Mproxy
	{
	private:
		int* sptr = nullptr;
		size_t pcols = 0;
	
	public:
		Mproxy(int* ptr, size_t cols);
		
		int operator[](size_t n) const;
		int& operator[](size_t n);
	};

	Matrix(const size_t r, const size_t c);
	~Matrix();
	
	size_t getRows();	
	size_t getColumns();

	bool operator==(const Matrix& a) const;
	bool operator!=(const Matrix& a) const;

	Matrix& operator*=(int n);
	
	const Mproxy operator[](size_t n) const;
	Mproxy operator[](size_t n);

};


#endif
