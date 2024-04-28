#pragma once
#include "big_int.hpp"

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
	auto max_size = std::max(_digits.size(), other._digits.size());
	auto digits = std::vector<unsigned int>(max_size);
	for (auto i = 0; i < max_size; i++)
	{
		auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
		auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;

		digits[max_size - i - 1] = op1 & op2;
	}

	return big_int(digits);
}

big_int big_int::operator | (const big_int& other) const
{
	auto max_size = std::max(_digits.size(), other._digits.size());
	auto digits = std::vector<unsigned int>(max_size);
	for (auto i = 0; i < max_size; i++)
	{
		auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
		auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;

		digits[max_size - i - 1] = op1 | op2;
	}

	return big_int(digits);
}
big_int big_int::operator ^ (const big_int& other) const
{
	auto max_size = std::max(_digits.size(), other._digits.size());
	auto digits = std::vector<unsigned int>(max_size);
	for (auto i = 0; i < max_size; i++)
	{
		auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
		auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;

		digits[max_size - i - 1] = op1 ^ op2;
	}

	return big_int(digits);
}

big_int big_int::operator << (int shift) const
{
	if (shift == 0) return *this;

	auto num = to_string(2);
	for (auto i = 0; i < shift; i++)
	{
		num += "0";
	}

	return big_int(num, 2);
}

big_int big_int::operator >> (int shift) const
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