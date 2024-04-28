#pragma once
#include "big_int.hpp"

bool big_int::operator == (const big_int& other) const
{
	if (_digits.size() != other._digits.size()) return false;
	
	for (auto i = 0; i < _digits.size(); i++)
	{
		if (_digits[i] != other._digits[i]) return false;
	}

	return true;
}

bool big_int::operator != (const big_int& other) const
{
	return !(*this == other);
}

bool big_int::operator < (const big_int& other) const
{
	auto shift_amount = uint_size - 1;
	if (_digits[0] >> shift_amount > other._digits[0] >> shift_amount) return true;
	else if (_digits[0] >> shift_amount < other._digits[0] >> shift_amount) return false;
	
	if (_digits.size() < other._digits.size()) return true;
	else if (_digits.size() > other._digits.size()) return false;

	return (_digits[0] < other._digits[0] == (_digits[0] >> shift_amount == 0));
}

bool big_int::operator <= (const big_int& other) const
{
	return *this < other || *this == other;
}

bool big_int::operator > (const big_int& other) const
{
	return !(*this < other) && *this != other;
}

bool big_int::operator >= (const big_int& other) const
{
	return *this > other || *this == other;
}