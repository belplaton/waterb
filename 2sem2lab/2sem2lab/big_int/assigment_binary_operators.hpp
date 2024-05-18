#pragma once
#include "big_int.hpp"

big_int& big_int::operator &= (const big_int& other)
{
	auto max_size = std::max(_digits.size(), other._digits.size());
	auto digits = std::vector<unsigned int>(max_size);
	for (auto i = 0; i < max_size; i++)
	{
		auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
		auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;

		digits[max_size - i - 1] = op1 & op2;
	}

	_digits = digits;

	return *this;
}

big_int& big_int::operator |= (const big_int& other)
{
	auto max_size = std::max(_digits.size(), other._digits.size());
	auto digits = std::vector<unsigned int>(max_size);
	for (auto i = 0; i < max_size; i++)
	{
		auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
		auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;

		digits[max_size - i - 1] = op1 | op2;
	}

	_digits = digits;

	return *this;
}

big_int& big_int::operator ^= (const big_int& other)
{
	auto max_size = std::max(_digits.size(), other._digits.size());
	auto digits = std::vector<unsigned int>(max_size);
	for (auto i = 0; i < max_size; i++)
	{
		auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
		auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;

		digits[max_size - i - 1] = op1 ^ op2;
	}

	_digits = digits;

	return *this;
}

big_int& big_int::operator <<= (unsigned int shift)
{
	int empty = 0;
	int macro_diff = 0;

	for (auto i = 0; i < _digits.size(); i++)
	{
		auto finished = false;
		for (auto j = 0; j < big_int::uint_size; j++)
		{
			int bit = get_bit(_digits[i], big_int::uint_size - j - 1);
			if (i == 0) bit &= ~sign_bit_mask;
			empty += bit > 0 ? 0 : 1;
			if (bit)
			{
				int temp1 = (shift - shift % big_int::uint_size) / big_int::uint_size;
				int temp2 = (shift % big_int::uint_size) - empty;
				macro_diff = temp1 + (temp2 > 0 ? 1 : 0);
				finished = true;
				break;
			}
		}

		if (finished) break;
	}

	int size = _digits.size() + macro_diff;
	auto result_digits = std::vector<unsigned int>(size);
	for (unsigned int k = 0; k < (_digits.size() * big_int::uint_size); k++)
	{
		auto i1 = (k - k % big_int::uint_size) / big_int::uint_size;
		auto i2 = ((k + shift) - (k + shift) % big_int::uint_size) / big_int::uint_size;

		auto j1 = k % big_int::uint_size;
		auto j2 = (k + shift) % big_int::uint_size;

		auto num = i1 < _digits.size() ? _digits[_digits.size() - i1 - 1] : 0;
		if (_digits.size() - i1 - 1 == 0) num &= ~sign_bit_mask;

		auto bit = get_bit(num, j1);
		if (bit) result_digits[size - i2 - 1] |= (bit << j2);
	}


	result_digits[0] |= big_int::sign_bit_mask * is_negate(*this);
	*this = big_int(result_digits); // cuz constructor can fix representation

	return *this;
}


big_int& big_int::operator >>= (unsigned int shift)
{
	int empty = 0;
	int macro_diff = 0;

	for (auto i = 0; i < _digits.size(); i++)
	{
		auto finished = false;
		for (auto j = 0; j < big_int::uint_size; j++)
		{
			int bit = get_bit(_digits[i], big_int::uint_size - j - 1);
			if (i == 0) bit &= ~sign_bit_mask;
			empty += bit > 0 ? 0 : 1;
			if (bit)
			{
				int temp1 = (shift - shift % big_int::uint_size) / big_int::uint_size;
				int temp2 = (shift % big_int::uint_size) - (empty);
				macro_diff = temp1 + (temp2 > 0 ? 1 : 0);
				finished = true;
				break;
			}
		}

		if (finished) break;
	}

	int size = _digits.size() + macro_diff;
	auto result_digits = std::vector<unsigned int>(size);
	for (unsigned int k = 0; k < (_digits.size() * big_int::uint_size); k++)
	{
		auto i2 = (k - k % big_int::uint_size) / big_int::uint_size;
		auto i1 = ((k + shift) - (k + shift) % big_int::uint_size) / big_int::uint_size;

		auto j2 = k % big_int::uint_size;
		auto j1 = (k + shift) % big_int::uint_size;

		auto num = i1 < _digits.size() ? _digits[_digits.size() - i1 - 1] : 0;
		if (_digits.size() - i1 - 1 == 0) num &= ~sign_bit_mask;

		auto bit = get_bit(num, j1);
		if (bit) result_digits[size - i2 - 1] |= (bit << j2);
	}


	result_digits[0] |= big_int::sign_bit_mask * is_negate(*this);
	*this = big_int(result_digits); // cuz constructor can fix representation

	return *this;
}
