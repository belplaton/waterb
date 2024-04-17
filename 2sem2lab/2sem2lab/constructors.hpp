#include "big_int.hpp"

big_int::big_int() : _size(0)
{
	_digits = new unsigned int[1];
}

big_int::big_int(bool sign, const unsigned int* digits, size_t size) : _size(size)
{
	_digits = new unsigned int[_size + 1];
	_digits[_size] = sign ? 0 : 1;

	if (digits == nullptr)
	{
		throw std::invalid_argument("Argument digits is null.");
	}

	std::copy(digits, digits + size, _digits + 1);
}



/*



*/