#pragma once
#include "big_int.hpp"
#include "constructors.hpp"

big_int& big_int::operator += (const big_int& other)
{
	auto left = *this;
	auto right = other;

	// Оптимизирование
	if (is_negate(_digits) && !is_negate(other._digits))
	{
		return *this = (right - (- left));
	}
	else if (!is_negate(_digits) && is_negate(other._digits))
	{
		return *this = -(left -= (-right));
	}

	auto max_size = std::max(_digits.size(), other._digits.size());
	auto result_digits = std::vector<unsigned int>(max_size);
	unsigned int carry = 0;
	for (unsigned int i = 0; i < max_size; i++)
	{
		auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
		if (i == _digits.size() - 1) op1 &= ~sign_bit_mask;

		auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;
		if (i == other._digits.size() - 1) op2 &= ~sign_bit_mask;

		auto result = add_with_carry(op1, op2, carry);

		carry = result.carry;
		result_digits[max_size - i - 1] = result.sum;
	}

	result_digits[0] |= sign_bit_mask * is_negate(_digits);
	*this = big_int(result_digits); // cuz constructor can fix representation

	return *this;
}

big_int& big_int::operator -= (const big_int& other)
{
	auto left = *this;
	auto right = other;

	// Оптимизирование
	if (is_negate(left) && !is_negate(right))
	{
		return *this = (left += -right);
	}
	else if (!is_negate(left) && is_negate(right))
	{
		return *this = (-left += right);
	}
	else if (left < right)
	{
		return *this = -(right - left);	
	}

	auto max_size = std::max(_digits.size(), other._digits.size()) + 1;
	auto result_digits = std::vector<unsigned int>(max_size);
	unsigned int borrow = 0;
	for (unsigned int i = 0; i < max_size; i++)
	{
		auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
		if (i == _digits.size() - 1) op1 &= ~sign_bit_mask;

		auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;
		if (i == other._digits.size() - 1) op2 &= ~sign_bit_mask;

		auto result = substract_with_borrow(op1, op2, borrow);

		borrow = result.borrow;
		result_digits[max_size - i - 1] = result.diff;
	}

	result_digits[0] |= sign_bit_mask * is_negate(_digits);
	*this = big_int(result_digits); // cuz constructor can fix representation

	return *this;
}

big_int& big_int::operator *= (const big_int& other)
{
	if (*this == 0 || other == 0)
	{
		*this = 0;
		return *this;
	}

	auto first_size = _digits.size() - ((_digits[0] & ~sign_bit_mask) == 0);
	auto second_size = other._digits.size() - ((other._digits[0] & ~sign_bit_mask) == 0);
	auto max_size = first_size + second_size;
	auto result_digits = std::vector<unsigned int>(max_size);
	auto k = 0ull;
	auto base = (1ull << big_int::uint_size);

	auto is_negative = big_int::is_negate(*this) ^ big_int::is_negate(other);

	for (unsigned int i = 0; i < second_size; i++)
	{
		auto carry = 0ull;
		k = max_size - i - 1;

		for (unsigned int j = 0; j < first_size; j++)
		{
			k = max_size - i - j - 1;

			auto op1 = other._digits[other._digits.size() - i - 1];
			if (i == other._digits.size() - 1) op1 &= ~sign_bit_mask;

			auto op2 = _digits[_digits.size() - j - 1];
			if (j == _digits.size() - 1) op2 &= ~sign_bit_mask;

			auto temp = (static_cast<unsigned long long>(op1) * static_cast<unsigned long long>(op2)) + carry + result_digits[k];

			carry = temp / base;
			result_digits[k] = temp % base;
		}

		result_digits[k - 1] += carry;
	}

	result_digits[0] |= sign_bit_mask * is_negative;
	*this = big_int(result_digits); // cuz constructor can fix representation

	return *this;
}

big_int& big_int::operator /= (const big_int& other)
{
	if (other == 0)
	{
		throw std::logic_error("Cant divide by zero");
	}

	if (other == 1)
	{
		return *this;
	}

	auto left = is_negate(*this) ? -*this : *this;
	auto right = is_negate(other) ? -other : other;
	auto is_negative = is_negate(*this) ^ is_negate(other);

	auto start_range = big_int();
	auto end_range = big_int(*this);
	auto potential_result = big_int();
	auto result = big_int();
	auto carry = big_int();

	do
	{
		potential_result = ((start_range + end_range) >> 1);
		result = potential_result * right;
		carry = left - result;

		if (carry >= 0 && carry < right)
		{
			potential_result._digits[0] |= sign_bit_mask * is_negative;
			*this = potential_result;
			return *this;
		}

		if (result > left)
		{
			end_range = potential_result;
		}
		else
		{
			start_range = potential_result;
		}

	} while (potential_result != 0 );

	throw std::logic_error("Error in divide function!");;
}


big_int& big_int::operator %= (const big_int& other)
{
	if (other == 0)
	{
		throw std::logic_error("Cant divide by zero");
	}

	if (other == 1)
	{
		return *this;
	}

	auto left = is_negate(*this) ? -*this : *this;
	auto right = is_negate(other) ? -other : other;
	auto is_negative = is_negate(*this) ^ is_negate(other);

	auto start_range = big_int();
	auto end_range = big_int(*this);
	auto potential_result = big_int();
	auto result = big_int();
	auto carry = big_int();

	do
	{
		potential_result = ((start_range + end_range) >> 1);
		result = potential_result * right;
		carry = left - result;

		if (carry >= 0 && carry < right)
		{
			carry._digits[0] |= sign_bit_mask * is_negative;
			*this = carry;
			return *this;
		}

		if (result > left)
		{
			end_range = potential_result;
		}
		else
		{
			start_range = potential_result;
		}

	} while (potential_result != 0);

	throw std::logic_error("Error in divide function!");;
}