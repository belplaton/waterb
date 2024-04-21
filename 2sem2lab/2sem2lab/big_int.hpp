#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

class big_int
{

private:

    const size_t uint_size = (sizeof(unsigned int) * 8);
    const unsigned int sign_bit_mask = 1 << (uint_size - 1);

    std::vector<unsigned int> _digits;

public:

    // Constructors

    big_int();

    big_int(const unsigned int* digits, size_t size);

    big_int(const std::vector<unsigned int>& digits);

    big_int(const std::string& number, size_t base);

    big_int(const big_int& other);

    ~big_int();

    // Relational operators

    bool operator == (const big_int& other) const;
    bool operator != (const big_int& other) const;
    bool operator < (const big_int& other) const;
    bool operator <= (const big_int& other) const;
    bool operator > (const big_int& other) const;
    bool operator >= (const big_int& other) const;

    // Arithmetic operators

    big_int operator + (const big_int& other);
    big_int operator - (const big_int& other);
    big_int operator * (const big_int& other);
    big_int operator / (const big_int& other);
    big_int operator % (const big_int& other);

    // Assigment operators

    big_int& operator += (const big_int& other);
    big_int& operator -= (const big_int& other);
    big_int& operator *= (const big_int& other);
    big_int& operator /= (const big_int& other);
    big_int& operator %= (const big_int& other);

    // Unary arithmetic operators

    big_int operator + () const;
    big_int operator - () const;

    // Binary arithemetic operators

    big_int operator ~ () const;
    big_int operator & (const big_int& other) const;
    big_int operator | (const big_int& other) const;
    big_int operator ^ (const big_int& other) const;
    big_int operator << (int shift) const;
    big_int operator >> (int shift) const;

    // IO stream operators
    
    friend std::ostream& operator << (std::ostream& stream, const big_int& other);
    friend std::istream& operator >> (std::istream& stream, big_int& number);

    // Utility

    inline static unsigned int get_bit(unsigned int num, unsigned int position)
    {
        return (num >> position) & 1;
    }

    inline unsigned int is_negate() const
    {
        return get_bit(_digits[0], uint_size - 1);
    }

    std::string to_string(unsigned int base) const;
};