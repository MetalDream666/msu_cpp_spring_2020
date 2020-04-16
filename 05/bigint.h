#ifndef BIGINT_H
#define BIGINT_H

#include <cstdlib>
#include <iostream>

class Bigint
{
private:
    uint8_t* num;
    bool sign;
    size_t len;
    
    Bigint(uint8_t* n, const bool s, const size_t l) : num(n), sign(s), len(l) {}

public:

	size_t getNumberOfDigits(const int64_t n) const;

    Bigint();
    Bigint(int64_t n);
    
    ~Bigint();

    bool operator==(const Bigint& n) const;
    bool operator!=(const Bigint& n) const;
    bool operator>(const Bigint& n) const;
    bool operator<(const Bigint& n) const;
    bool operator>=(const Bigint& n) const;
    bool operator<=(const Bigint& n) const;
    
    Bigint(const Bigint& n);
    Bigint& operator=(int64_t n);
    Bigint& operator=(const Bigint& n);

	bool cmp_abs(const Bigint& n1, const Bigint& n2) const;

    Bigint operator+(const Bigint& n) const;
    Bigint operator-() const;
    Bigint operator-(const Bigint& n) const;

    friend std::ostream& operator<<(std::ostream& out, const Bigint& n);
};

#endif
