#pragma once
#include "big_int.hpp"
#include "assigment_arithmetic_operators.hpp"
#include "binary_operators.hpp"
#include "relational_operators.hpp"
#include <bitset>

big_int big_int::operator + () const
{
	return *this;
}

big_int big_int::operator - () const
{
	auto temp(*this);
	temp._digits[0] ^= sign_bit_mask;

	return temp;
}

big_int big_int::operator + (const big_int& other) const
{
	auto temp = big_int(*this);
	temp += other;

	return temp;
}

big_int big_int::operator - (const big_int& other) const
{
	auto temp = big_int(*this);
	temp -= other;

	return temp;
}

/*
big_int big_int::operator * (const big_int& other) const
{
	auto result = big_int();
	auto temp = big_int(other);

	for (int i = _digits.size() - 1; i >= 0; --i) {
		for (int j = 0; j < sizeof(unsigned int) * 8; ++j) {
			if ((_digits[i] & (1 << j)) != 0) {
				result = result + temp;
			}

			temp <<= 1;
		}
		temp = temp >> (sizeof(unsigned int) * 8);
		result <<= 1;
	}

	return result;
}
*/