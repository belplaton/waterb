#pragma once
#include "big_int.hpp"

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
		if (i == 0 && ((digits[i] & ~sign_bit_mask) == 0))
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
	for (auto i = 0; i < real_size; i++)
	{
		_digits[i] = digits[i + diff];
	}

	_digits[0] |= sign_bit_mask * is_negate(digits);
}

big_int::big_int(const unsigned int* digits, size_t size)
{
	size_t real_size = 1;
	size_t diff = 0;

	for (auto i = 0; i < size; i++)
	{
		if (i == 0 && ((digits[i] & ~sign_bit_mask) == 0))
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
	for (auto i = 0; i < real_size; i++)
	{
		_digits[i] = digits[i + diff];
	}

	_digits[0] |= sign_bit_mask * is_negate(digits);
}

big_int::big_int(const std::string& number, size_t base)
{
	if (base < 2 || base > 36)
	{
		throw std::invalid_argument("Invalid base.");
	}

	int is_negative = (number[0] == '-');

	for (auto i = is_negative; i < number.size(); i++)
	{
		if (!isdigit(number[i]) && !isalpha(number[i]))
		{
			throw std::invalid_argument("Invalid character in number");
		}
	}

	auto dec_string = from_base_to_dec(number, base);

	std::cout << dec_string << std::endl;

	auto bin_string = from_dec_to_base(dec_string, 2);
	std::cout << bin_string << std::endl;

	auto temp1 = (bin_string.size() % big_int::uint_size) != 0;
	auto temp2 = (bin_string.size() - (bin_string.size() % big_int::uint_size)) / big_int::uint_size;
	auto size = temp1 + temp2;
	_digits = std::vector<unsigned int>(size);


	auto k = 0;
	for (auto i = 0; i < size; i++)
	{
		for (auto j = 0; j < big_int::uint_size && j < bin_string.size(); j++)
		{
			auto bit = char_to_int(bin_string[bin_string.size() - k - 1], 2);
			_digits[size - i - 1] |= (bit << j);
			k++;

			if (k == (bin_string.size() - is_negative)) break;
		}

		if (k == (bin_string.size() - is_negative)) break;
	}

	_digits[0] |= sign_bit_mask * is_negative;
}

big_int::big_int(const big_int& other)
{
	_digits = std::vector<unsigned int>(other._digits);
}

big_int::~big_int()
{
	
}