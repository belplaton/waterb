#pragma once

#include "big_int.hpp"
#include "utility.hpp"
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

big_int big_int::operator + (const big_int& other)
{
	/*

	if (is_negate() && !other.is_negate())
	{
		return *this - other;
	}
	else if (!is_negate() && other.is_negate())
	{
		return other& - *this;
	}

	*/

	auto first_size = _digits.size();
	auto second_size = other._digits.size();
	auto max_size = std::max(first_size, second_size);


	for (auto i = 0; i < max_size; i++)
	{
		std::cout << '[' << std::bitset<32>(_digits[i]) << "], " << '[' << std::bitset<32>(other._digits[i]) << "], " << std::endl;

		auto is_expanded = false;
		auto is_continue = true;
		for (auto j = 1; j < uint_size; j++)
		{
			auto op1 = (i < first_size) ? get_bit(_digits[i], uint_size - j - (i == 0)) : 0;
			auto op2 = (i < second_size) ? get_bit(other._digits[i], uint_size - j - (i == 0)) : 0;



			std::cout << '[' << op1 << ',' << op2 << ']' << std::endl;

			if (!op1 && !op2)
			{
				is_continue = false;
				break;
			}
			else if (op1 && op2)
			{
				max_size++;
				is_expanded = true;
				break;
			}
		}

		if (is_expanded || !is_continue) break;
	}

	auto result_digits = std::vector<unsigned int>(max_size);
	unsigned int carry = 0;
	for (auto i = 0; i < max_size; i++)
	{
		auto op1 = (i < first_size) ? _digits[first_size - i - 1] : 0;
		if (i == first_size - 1) op1 &= ~sign_bit_mask;

		auto op2 = (i < second_size) ? other._digits[second_size - i - 1] : 0;
		if (i == second_size - 1) op2 &= ~sign_bit_mask;

		std::cout << "OPERANDS: " << op1 << " " << op2 << " " << carry << std::endl;
		auto result = add_with_carry(op1, op2, carry);

		carry = result.carry;
		result_digits[max_size - i - 1] = result.sum;

		std::cout << "SUM: " << result.sum << ", CARRY: " << carry << '\n' << std::endl;
	}
	
	result_digits[0] |= sign_bit_mask * is_negate();

	return big_int(result_digits);
}

/*

big_int big_int::operator - (const big_int& other)
{

	if ((_digits[0] & sign_bit_mask) && !(other._digits[0] & sign_bit_mask))
	{
		return *this + other;
	}
	else if (!(_digits[0] & sign_bit_mask) && (other._digits[0] & sign_bit_mask))
	{
		return -(other& + *this);
	}

	auto sign = _digits[0] & sign_bit_mask;

	auto first_size = _digits.size();
	auto second_size = other._digits.size();

	auto first_extra = (_digits[0] & sign_bit_mask) != 0;
	auto second_extra = (other._digits[0] & sign_bit_mask) != 0;

	auto max_size = std::max(first_size + first_extra, second_size + second_extra);
	auto result_digits = std::vector<unsigned int>(max_size);

	unsigned int carry = 0;
	for (auto i = 0; i < max_size; i++)
	{
		auto op1 = (i < first_size) ? _digits[first_size - i - 1] : 0;
		if (i == first_size - 1) op1 &= sign_bit_mask;

		auto op2 = (i < second_size) ? other._digits[second_size - i - 1] : 0;
		if (i == second_size - 1) op2 &= sign_bit_mask;

		// std::cout << "OPERANDS: " << op1 << " " << op2 << " " << carry << std::endl;
		auto diff = op1 - op2;
		if (diff > op1)
		{
			for (auto j = i + 1; j < max_size; j++)
			{
			}
		}

		result_digits[max_size - i - 1] = 0;

		std::cout << "SUM: " << 0 << ", CARRY: " << carry << '\n' << std::endl;
	}

	result_digits[0] |= sign_bit_mask * sign;

	return big_int(result_digits);
}

*/