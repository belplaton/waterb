#pragma once
#include "big_int.hpp"

#pragma region Default

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

	if (big_int::is_negate(*this) && !big_int::is_negate(other)) return true;
	else if (!big_int::is_negate(*this) && big_int::is_negate(other)) return false;

	if (_digits.size() < other._digits.size()) return !big_int::is_negate(*this);
	else if (_digits.size() > other._digits.size()) return big_int::is_negate(*this);

	for (auto i = 0; i < _digits.size(); i++)
	{
		auto op1 = _digits[i];
		if (i == 0) op1 &= ~sign_bit_mask;

		auto op2 = other._digits[i];
		if (i == 0) op2 &= ~sign_bit_mask;

		if (op1 < op2) return !big_int::is_negate(*this);
		else if (op1 > op2) return big_int::is_negate(*this);
	}

	return false;
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


#pragma endregion

#pragma region Integer

bool big_int::operator == (int other) const
{
	return *this == big_int(other);
}

bool big_int::operator != (int other) const
{
	return *this != big_int(other);
}

bool big_int::operator < (int other) const
{
	return *this < big_int(other);
}

bool big_int::operator <= (int other) const
{
	return *this <= big_int(other);
}

bool big_int::operator > (int other) const
{
	return *this > big_int(other);
}

bool big_int::operator >= (int other) const
{
	return *this >= big_int(other);
}

#pragma endregion