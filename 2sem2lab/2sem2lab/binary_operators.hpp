#pragma once
#include "big_int.hpp"
#include "assigment_binary_operators.hpp"

big_int big_int::operator ~ () const
{
	auto digits = std::vector<unsigned int>(_digits.size());
	for (auto i = 0; i < _digits.size(); i++)
	{
		digits[i] = (~_digits[i]);
	}

	return big_int(digits);
}

big_int big_int::operator & (const big_int& other) const
{
	auto temp = big_int(*this);
	temp &= other;

	return temp;
}

big_int big_int::operator | (const big_int& other) const
{
	auto temp = big_int(*this);
	temp |= other;

	return temp;
}
big_int big_int::operator ^ (const big_int& other) const
{
	auto temp = big_int(*this);
	temp ^= other;

	return temp;
}

big_int big_int::operator << (unsigned int shift) const
{
	auto temp = big_int(*this);
	temp <<= shift;

	return temp;
}

big_int big_int::operator >> (unsigned int shift) const
{
	auto temp = big_int(*this);
	temp >>= shift;

	return temp;
}
