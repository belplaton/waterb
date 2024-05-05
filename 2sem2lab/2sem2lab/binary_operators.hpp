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
	if (shift == 0) return *this;

	auto num = to_string(2);
	auto is_negate = (num[0] == '-');
	auto final_num = "";

	for (auto i = is_negate; i < num.size() - is_negate - shift; i++)
	{
		final_num += num[i];
	}

	if (final_num == "")
	{
		final_num = "0";
	}
	else if (is_negate)
	{
		final_num = '-' + final_num;
	}

	return big_int(final_num, 2);
}
