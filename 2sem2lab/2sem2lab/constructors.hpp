#pragma once

#include "big_int.hpp"

/*

big_int::big_int(bool sign, const unsigned int* digits, size_t size) : _size(size)
{
	_digits = new unsigned int[_size + 1];
	_digits[_size] = sign ? 0 : 1;

	if (digits == nullptr)
	{
		throw std::invalid_argument("Argument digits is null.");
	}

	std::copy(digits, digits + size, _digits + 1);
}


*/

big_int::big_int()
{
	_digits = std::vector<unsigned int>(1);
}

big_int::big_int(const std::vector<unsigned int>& digits)
{
	size_t real_size = 1;
	size_t diff = 0;

	for (auto i = 0; i < digits.size(); i++)
	{
		if (i == 0 && (digits[i] & ~sign_bit_mask) == 0)
		{
			continue;
		}

		if (digits[i] != 0)
		{
			real_size = digits.size() - i;
			diff = i;
			break;
		}
	}

	_digits = std::vector<unsigned int>(real_size);
	for (auto i = real_size; i < digits.size(); i++)
	{
		_digits[i - real_size] = digits[i];
	}

	_digits[0] |= sign_bit_mask * is_negate(_digits);
}

big_int::big_int(const unsigned int* digits, size_t size)
{
	size_t real_size = 1;
	size_t diff = 0;

	for (auto i = 0; i < size; i++)
	{
		if (i == 0 && (digits[i] & ~sign_bit_mask) == 0)
		{
			continue;
		}

		if (digits[i] != 0)
		{
			real_size = size - i;
			diff = i;
			break;
		}
	}

	_digits = std::vector<unsigned int>(real_size);
	for (auto i = real_size; i < size; i++)
	{
		_digits[i - real_size] = digits[i];
	}

	_digits[0] |= sign_bit_mask * is_negate(_digits);
}

big_int::big_int(const std::string& number, size_t base)
{
	if (base < 2 || base > 10)
	{
		throw std::invalid_argument("Invalid base.");
	}

	bool is_negative = number[0] == '-';
	size_t start_index = number[0] == '-';

	for (auto i = start_index; i < number.size(); i++)
	{
		if (!isdigit(number[i]))
		{
			throw std::invalid_argument("Invalid character in number");
		}
	}

	for (size_t i = start_index; i < number.size(); ++i) {
		unsigned int digit = number[i] - '0';

		/* TO DO: через операторы с uint сделать добавление чисел
		*this *= base;
		*this += digit;
		*/
	}
}

big_int::big_int(const big_int& other)
{
	_digits = std::vector<unsigned int>(other._digits);
}

big_int::~big_int()
{
	
}