#pragma once
#ifndef _POLYNOMIAL_
#define _POLYNOMIAL_

#include "../big_int/big_int.hpp"
#include "../big_float/big_float.hpp"

struct polynomial_data
{
	big_int degree;
	big_float coefficient;

	polynomial_data(big_int degree, big_float coefficient) : degree(degree), coefficient(coefficient)
	{

	}
};

class polynomial
{

};

#endif // ! _POLYNOMIAL_
