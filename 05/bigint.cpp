#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "bigint.h"


size_t Bigint::getNumberOfDigits(const int64_t n) const
{
	size_t i = std::ceil(std::log10(n));
	if (n < 2)
	{
		i = 1;
	}
	return i;
}

Bigint::Bigint()
{
	num = new uint8_t[1];
	num[0] = 0;
	sign = true;
	len = 1;
}

Bigint::Bigint(int64_t n)
{
	sign = true;
	if (n < 0)
	{
		sign = false;
		n = -n;
	}

	size_t i = getNumberOfDigits(n);
	len = i;
	num = new uint8_t[i];
	while (n != 0)
	{
		i--;
		num[i] = n % 10;
		n /= 10;
	}
}

bool Bigint::operator==(const Bigint& n) const
{
	if (this == &n)
	{
		return true;
	}
	else if (len == n.len)
	{
		if (sign == n.sign)
		{
			if (num == n.num)
			{
				return true;
			}
			else return (memcmp(num, n.num, n.len) == 0);
		}
	}

	return false;
}

bool Bigint::operator!=(const Bigint& n) const
{
	return (!(*this == n));
}

bool Bigint::operator>(const Bigint& n) const
{
	if (this == &n)
	{
		return false;
	}
	else if (sign && !n.sign)
	{
		return true;
	}
	else if (!sign && n.sign)
	{
		return false;
	}
	else
	{
		bool ans;
		if (len != n.len)
		{
			ans = len > n.len;
		}
		else
		{
			int a = std::memcmp(num, n.num, len);
			ans = (a > 0);
		}
		if (sign && n.sign)
		{
			return ans;
		}
		else
		{
			return !ans;
		}
	}
}

bool Bigint::operator<(const Bigint& n) const
{
	return !((*this > n) || (*this == n));
}

bool Bigint::operator>=(const Bigint& n) const
{
	return !(*this < n);
}

bool Bigint::operator<=(const Bigint& n) const
{
	return !(*this > n);
}


Bigint::Bigint(const Bigint& n)
{
	if (this != &n)
	{
		len = n.len;
		sign = n.sign;
		if (num != n.num)
		{
			uint8_t* new_num = new uint8_t[n.len];
			std::memcpy(new_num, n.num, n.len);
			delete[] num;
			num = new_num;
		}
	}
}

Bigint& Bigint::operator=(int64_t n)
{
	if (n < 0)
	{
		sign = false;
		n = -n;
	}
	size_t i = getNumberOfDigits(n);
	len = i;
	uint8_t* new_num = new uint8_t[i];
	while (n != 0)
	{
		i--;
		new_num[i] = n % 10;
		n /= 10;
	}
	delete[] num;
	num = new_num;
	return *this;
}

Bigint& Bigint::operator=(const Bigint& n)
{
	if (this == &n)
	{
		return *this;
	}
	sign = n.sign;
	len = n.len;
	if (num != n.num)
	{
		uint8_t* new_num = new uint8_t[n.len];
		std::memcpy(new_num, n.num, n.len);
		delete[] num;
		num = new_num;
	}
	return *this;
}

Bigint::~Bigint()
{
	delete[] num;
}


bool Bigint::cmp_abs(const Bigint& n1, const Bigint& n2) const
{
	bool ans;
	if (n1.len != n2.len)
	{
		ans = n1.len < n2.len;
	}
	else
	{
		int a = std::memcmp(n1.num, n2.num, n1.len);
		ans = (a < 0);
	}
	return ans;
}

Bigint Bigint::operator+(const Bigint& n) const
{
	size_t new_len = std::max(len, n.len);
	bool new_sign = sign;
	uint8_t* new_num = nullptr;

	if (sign == n.sign)
	{
		if (len < n.len)
		{
			return n + (*this);
		}
		size_t i = len; // i >= j
		size_t j = n.len;
		size_t k = new_len;
		uint8_t plus = 0;
		uint8_t sum = 0;
		uint8_t* s = new uint8_t[new_len];
		while (i != 0)
		{
			i--;
			j--;
			k--;
			if (j >= 0)
			{
				sum = num[i] + n.num[j];
			}
			if (plus != 0)
			{
				sum += plus;
				plus = 0;
			}
			if (sum >= 10)
			{
				plus++;
				sum %= 10;
			}
			s[k] = sum;
			sum = 0;
		}
		if (plus != 0)
		{
			new_len++;
			new_num = new uint8_t[new_len];
			new_num[0] = plus;
			std::memcpy(new_num + 1, s, new_len - 1);
		}
		else
		{
			new_num = new uint8_t[new_len];
			std::memcpy(new_num, s, new_len);
		}
		delete[] s;
		return Bigint(new_num, new_sign, new_len);
	}
	else
	{
		
		if(cmp_abs(*this, n))
		{
			return (n + *this);
		}
		else
		{
			// len >= n.len
			size_t i = len;
			size_t j = n.len;
			size_t k = new_len;
			int8_t minus = 0;
			int8_t raz = 0;
			int8_t* r = new int8_t[new_len];
			while (i != 0)
			{
				i--;
				j--;
				k--;
				if (j >= 0)
				{
					raz = num[i] - n.num[j];
				}
				if (minus != 0)
				{
					raz -= minus;
					minus = 0;
				}
				if (raz < 0)
				{
					minus++;
					raz = std::abs(raz);
				}
				r[k] = raz;
				raz = 0;
			}
			new_num = new uint8_t[new_len];
			std::memcpy(new_num, r, new_len);
			delete[] r;
			return Bigint(new_num, new_sign, new_len);
		}
	}
}

Bigint Bigint::operator-() const
{
	uint8_t* new_num = new uint8_t[len];
	std::memcpy(new_num, num, len);
	Bigint new_n = Bigint(new_num, !(sign), len);
	return new_n;
}

Bigint Bigint::operator-(const Bigint& n) const
{
	if (sign == n.sign)
	{
		return (*this + (-n));
	}
	return (*this + n);
}

std::ostream& operator<<(std::ostream& out, const Bigint& n)
{
	if (!n.sign)
	{
		out << "-";
	}
	for (size_t i = 0; i < n.len; i++)
	{
		out << unsigned(n.num[i]);
	}
	return out;
}

