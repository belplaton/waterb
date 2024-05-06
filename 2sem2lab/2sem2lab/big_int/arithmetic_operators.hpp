#pragma once
#include "big_int.hpp"
#include "assigment_arithmetic_operators.hpp"
#include "binary_operators.hpp"
#include "relational_operators.hpp"
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

big_int big_int::operator + (const big_int& other) const
{
	auto temp = big_int(*this);
	temp += other;

	return temp;
}

big_int big_int::operator - (const big_int& other) const
{
	auto temp = big_int(*this);
	temp -= other;

	return temp;
}

big_int big_int::operator * (const big_int& other) const
{
	auto temp = big_int(*this);
	temp *= other;

	return temp;
}

big_int big_int::operator / (const big_int& other) const
{
	auto temp = big_int(*this);
	temp /= other;

	return temp;
}

big_int big_int::operator % (const big_int& other) const
{
	auto temp = big_int(*this);
	temp %= other;

	return temp;
}