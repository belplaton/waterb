#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

class big_int
{

private:

    unsigned int* _digits;
    size_t _size;

public:

    // Constructors

    big_int();

    big_int(bool sign, const unsigned int* digits, size_t size);

    big_int(bool sign, const std::vector<unsigned int>& digits);

    big_int(const std::string& number, size_t base);

    // Relational operators

    bool operator == (const big_int& other) const;
    bool operator != (const big_int& other) const;
    bool operator < (const big_int& other) const;
    bool operator <= (const big_int& other) const;
    bool operator > (const big_int& other) const;
    bool operator >= (const big_int& other) const;

    big_int& operator + (const big_int& other);
    big_int& operator - (const big_int& other);
    big_int& operator * (const big_int& other);
    big_int& operator / (const big_int& other);
    big_int& operator % (const big_int& other);

    big_int& operator += (const big_int& other);
    big_int& operator -= (const big_int& other);
    big_int& operator *= (const big_int& other);
    big_int& operator /= (const big_int& other);
    big_int& operator %= (const big_int& other);

    big_int operator ~ () const;
    big_int operator & (const big_int& other) const;
    big_int operator | (const big_int& other) const;
    big_int operator ^ (const big_int& other) const;
    big_int operator << (int shift) const;
    big_int operator >> (int shift) const;

    friend std::ostream& operator << (std::ostream& stream, const big_int& number);
    friend std::istream& operator >> (std::istream& stream, big_int& number);

};