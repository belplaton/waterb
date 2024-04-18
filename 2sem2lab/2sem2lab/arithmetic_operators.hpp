#pragma once

#include "big_int.hpp"
#include "utility.hpp"

big_int big_int::operator + (const big_int& other)
{
	auto result_digits = std::vector<unsigned int>();
	auto first_size = _digits.size();
	auto second_size = other._digits.size();

	auto first_extra = (_digits[0] & ~(1 << (uint_size - 1))) != 0;
	auto second_extra = (other._digits[0] & ~(1 << (uint_size - 1))) != 0;

	auto max_size = std::max(first_size+first_extra, second_size+second_extra);

	result_digits.resize(max_size, 0);
	unsigned int carry = 0;

	for (auto i = 0; i < max_size; i++)
	{
		auto op1 = (i < first_size) ? _digits[first_size - i - 1] : 0;
		if (i == first_size - 1) op1 &= ~(1 << (uint_size - 1));

		auto op2 = (i < second_size) ? other._digits[second_size - i - 1] : 0;
		if (i == second_size - 1) op2 &= ~(1 << (uint_size - 1));

		auto result = add_with_carry(op1, op2, carry);

		carry = result.carry;
		result_digits[max_size - i - 1] = result.sum;

		std::cout << "sum: " << result.sum << " carry: " << carry << std::endl;
	}

	return big_int(result_digits);
}