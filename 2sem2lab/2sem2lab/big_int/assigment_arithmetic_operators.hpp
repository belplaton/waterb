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
		return *this = (left -= right);
	}
	else if (!is_negate(_digits) && is_negate(other._digits))
	{
		return *this = -(left -= (-right));
	}

	auto max_size = check_for_size_change(_digits, other._digits, true);
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
	_digits = result_digits;

	return *this;
}

big_int& big_int::operator -= (const big_int& other)
{
	auto left = *this;
	auto right = other;

	// Оптимизирование
	if (is_negate(left) && !is_negate(right))
	{
		std::cout << "A: " << _digits << " " << other._digits << std::endl;
		return *this = (left += -right);
	}
	else if (!is_negate(left) && is_negate(right))
	{
		std::cout << "B: " << _digits << " " << other._digits << std::endl;
		return *this = (-left += right);
	}
	else if (left < right)
	{
		std::cout << "C: " << _digits << " " << other._digits << std::endl;
		return *this = -(right - left);	
	}

	auto max_size = check_for_size_change(_digits, other._digits, false);
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
	_digits = result_digits;

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

	auto negate = big_int::is_negate(*this) | big_int::is_negate(other);

	for (unsigned int i = 0; i < second_size; i++)
	{
		auto carry = 0ull;
		k = max_size - i - 1;

		for (unsigned int j = 0; j < first_size; j++)
		{
			k = max_size - i - j - 1;

			auto op1 = other._digits[other._digits.size() - i - 1];
			//if (i == other._digits.size() - 1) op1 &= ~sign_bit_mask;

			auto op2 = _digits[_digits.size() - j - 1];
			//if (j == _digits.size() - 1) op2 &= ~sign_bit_mask;

			auto temp = (static_cast<unsigned long long>(op1) * static_cast<unsigned long long>(op2)) + carry + result_digits[k];

			carry = temp / base;
			std::cout << "A " << temp << " " << carry << " " << base << std::endl;
			result_digits[k] = temp % base;
		}

		result_digits[k - 1] += carry;
	}

	_digits = result_digits;

	return *this;
}

big_int& big_int::operator /= (const big_int& other)
{
	auto start_range = big_int();
	auto end_range = *this;
	auto potential_result = big_int();
	auto result = big_int();
	auto carry = big_int();

	do {
		potential_result = ((start_range + end_range) >> 1);
		result = potential_result * other;
		carry = *this - result;

		std::cout << potential_result << " " << result << " " << carry << std::endl;

		if (carry >= 0 && carry < other) {
			*this = potential_result;
			return *this;
		}
		if (result > *this) {
			end_range = potential_result;
		}
		else {
			start_range = potential_result;
		}

	} while (potential_result != 0);

	throw std::logic_error("Error in divide function!");;
}


big_int& big_int::operator %= (const big_int& other)
{
	auto start_range = big_int();
	auto end_range = *this;
	auto potential_result = big_int();
	auto result = big_int();
	auto carry = big_int();

	do {
		potential_result = ((start_range + end_range) >> 1);
		result = potential_result * other;
		carry = *this - result;

		if (carry >= 0 && carry < other) {
			*this = carry;
			return *this;
		}
		if (result > *this) {
			end_range = potential_result;
		}
		else {
			start_range = potential_result;
		}

	} while (potential_result != 0);

	throw std::logic_error("Error in mod2 function!");;
}