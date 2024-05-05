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

big_int big_int::operator << (unsigned int shift) const
{
	int empty = 0;
	int macro_diff = 0;

	for (auto i = 0; i < _digits.size(); i++)
	{
		auto finished = false;
		for (auto j = 0; j < big_int::uint_size; j++)
		{
			int bit = get_bit(_digits[i], big_int::uint_size - j - 1);
			empty += bit > 0 ? 0 : 1;
			if (bit)
			{
				int temp1 = (shift - shift % big_int::uint_size) / big_int::uint_size;
				int temp2 = (shift % big_int::uint_size) - empty;
				macro_diff = temp1 + (temp2 > 0 ? 1 : 0);
				finished = true;
				break;
			}

			std::cout << "I: " << i << " J: " << j << std::endl;

		}

		if (finished) break;
	}

	int size = _digits.size() + macro_diff;
	//std::cout << "A: " << _digits.size() << " B: " << size << std::endl;

	auto result_digits = std::vector<unsigned int>(size);
	for (auto i = 0; i < _digits.size(); i++)
	{
		for (auto j = 0; j < big_int::uint_size; j++)
		{
			auto i1 = i + ((j + shift) - ((j + shift) % big_int::uint_size)) / big_int::uint_size;
			auto j1 = (j + shift) % big_int::uint_size;


			auto num = _digits[i];
			if (i == 0) num &= ~sign_bit_mask;

			//std::cout << "K: " << k << " I: " << i << " J: " << j << " I1: " << i1 << " J1: " << j1 << " SIZE: " << _digits.size() << std::endl;

			if (i1 <= i)
			{
				auto bit = get_bit(num, (big_int::uint_size - j1 - 1));
				result_digits[i1] |= bit << (big_int::uint_size - j - 1);
			}
		}
	}

	result_digits[0] |= big_int::sign_bit_mask * is_negate(*this);

	return big_int(result_digits);
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