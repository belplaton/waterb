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
	auto empty = 0;
	auto micro_diff = 0;
	auto macro_diff = 0;
	for (auto i = 0; i < _digits.size(); i++)
	{
		auto finished = false;
		for (auto j = 0; j < big_int::uint_size; j++)
		{
			auto bit = get_bit(_digits[i], big_int::uint_size - j - 1);
			empty += bit > 0 ? 1 : 0;
			if (bit)
			{
				micro_diff = empty % big_int::uint_size;
				macro_diff = empty / big_int::uint_size + (empty % big_int::uint_size > 1 ? 1 : 0);
				finished = true;
				break;
			}
		}

		if (finished) break;
	}

	unsigned int size = _digits.size() + macro_diff;

	auto result_digits = std::vector<unsigned int>(size);
	for (auto i = 0; i < _digits.size(); i++)
	{
		for (auto j = 0; j < big_int::uint_size; j++)
		{
			auto k = j + (shift % big_int::uint_size);

			auto a1 = k % big_int::uint_size;
			auto a2 = (k - k % big_int::uint_size - micro_diff) / big_int::uint_size;

			if (k < big_int::uint_size)
			{
				result_digits[i] |= get_bit(_digits[i], (big_int::uint_size - k - 1)) << (big_int::uint_size - j - 1);
				std::cout << (big_int::uint_size - j - 1) << " " << (big_int::uint_size - k - 1) << std::endl;
			}
			else
			{
				result_digits[i] |= get_bit(_digits[i + a2], (big_int::uint_size - j - shift - 1)) << (big_int::uint_size - j - 1);
				std::cout << i + a2 << " " << (big_int::uint_size - j - a1 - 1) << " " << (big_int::uint_size - j - 1) << std::endl;
			}
		}
	}

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