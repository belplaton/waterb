#pragma once
#include "big_int.hpp"

// TODO: ����������� += � +
big_int& big_int::operator += (const big_int& other)
{
	auto left = *this;
	auto right = other;

	// ���������������
	if (is_negate(_digits) && !is_negate(other._digits))
	{
		return *this = (left -= right);
	}
	else if (!is_negate(_digits) && is_negate(other._digits))
	{
		return *this = -(left -= (-right));
	}

	auto max_size = check_for_size_change(_digits, other._digits, true);
	auto result_digits = std::vector<unsigned int>(max_size);
	unsigned int carry = 0;
	for (auto i = 0; i < max_size; i++)
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
	_digits = result_digits;

	return *this;
}

big_int& big_int::operator -= (const big_int& other)
{
	auto left = *this;
	auto right = other;

	// ���������������
	if (is_negate(_digits) && !is_negate(other._digits))
	{
		return *this = (left += -right);
	}
	else if (!is_negate(_digits) && is_negate(other._digits))
	{
		return *this = (-left += right);
	}
	else if (*this < other)
	{
		return *this = (left -= right);
	}

	auto max_size = check_for_size_change(_digits, other._digits, false);
	auto result_digits = std::vector<unsigned int>(max_size);
	unsigned int borrow = 0;
	for (auto i = 0; i < max_size; i++)
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
	_digits = result_digits;

	return *this;
}


/*
big_int& big_int::operator *= (const big_int& other)
{
	auto temp = *this * other;
	*this = temp;

	return *this;
}

big_int& big_int::operator /= (const big_int& other)
{
	auto temp = *this / other;
	*this = temp;

	return *this;
}

big_int& big_int::operator %= (const big_int& other)
{
	auto temp = *this % other;
	*this = temp;

	return *this;
}
*/