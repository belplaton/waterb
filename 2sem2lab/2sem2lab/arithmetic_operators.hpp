#include "big_int.hpp"

big_int& big_int::operator + (const big_int& other)
{
	auto uint_size = (sizeof(unsigned int) * 8);

	auto smaller = *this < other ? *this : other;
	auto bigger = *this == smaller ? other : *this;

	auto result_size = bigger._size + 1;
	auto result_digits = new int[result_size];
	auto carry = 0;

	unsigned int this_num = 0;
	unsigned int other_num = 0;
	for (auto i = result_size - 1; i > 0; i--)
	{
		if (i < _size)
		{
			this_num = _digits[i];
		}

		if (i < other._size)
		{
			other_num = other._digits[i];
		}

		result_digits[i] = this_num + other_num + carry;
		carry = this_num >> (uint_size - 2) * other_num >> (uint_size - 2);
	}

	this_num = _digits[0] & ~(1 << (uint_size - 1));
	other_num = other._digits[0] & ~(1 << (uint_size - 1));
	result_digits[0] = this_num + other_num + carry;

	if (result_digits[0] & (1 << (uint_size - 1)))
	{

	}
	else
	{
		result_digits[0] |= _digits[0] & (1 << (uint_size - 1));
	}
}