#include <stdexcept>
#include <iostream>
#include <cstring>

#include "matrix.h"

Matrix::Mproxy::Mproxy(int* ptr, size_t cols): sptr(ptr), pcols(cols) {} 
		
int Matrix::Mproxy::operator[](size_t n) const
{
	if(n >= pcols)
	{
		throw std::out_of_range("OUT OF RANGE");
	}
		
	return sptr[n];
}
		
int& Matrix::Mproxy::operator[](size_t n)
{
	if(n >= pcols)
	{
		throw std::out_of_range("OUT OF RANGE");
	}
	
	return sptr[n];
}


Matrix::Matrix(const size_t r, const size_t c): rows(r), cols(c) 
{
	if((rows == 0) || (cols == 0))
	{
		throw std::out_of_range("one of dimensions is zero");
	}
	matr = (int*)malloc(rows * cols * sizeof(int));
	if(matr == nullptr)
	{
		throw std::runtime_error("failed to allocate memory");
	}
}
	
Matrix::~Matrix()
{
	free(matr);
}
	
size_t Matrix::getRows()
{
	return rows;
}

size_t Matrix::getColumns()
{
	return cols;
}
	
bool Matrix::operator==(const Matrix& a) const
{
	if(this == &a)
	{
		return true;
	}

	if((rows != a.rows) || (cols != a.cols))
	{
		return false;
	}

	return (memcmp(matr, a.matr, cols*rows*sizeof(int)) == 0);
}
	
bool Matrix::operator!=(const Matrix& a) const
{
	return !(*this == a);
}

Matrix& Matrix::operator*=(int n)
{
	for(size_t i = 0; i < cols*rows; i++)
	{
		matr[i] *= n;
	}
	return *this;
}
	
const Matrix::Mproxy Matrix::operator[](size_t n) const
{
	return Mproxy(matr + cols*n, cols);
}
	
Matrix::Mproxy Matrix::operator[](size_t n)
{
	return Mproxy(matr + cols*n, cols);
}0

