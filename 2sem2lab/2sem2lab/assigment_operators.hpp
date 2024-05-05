#pragma once

#include "big_int.hpp"
#include "arithmetic_operators.hpp"

// TODO: переставить += и +
big_int& big_int::operator += (const big_int& other)
{
	auto temp = *this + other;
	*this = temp;

	return *this;
}

big_int& big_int::operator -= (const big_int& other)
{
	auto temp = *this - other;
	*this = temp;

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