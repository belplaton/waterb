#pragma once
#ifndef _BIGFLOAT_
#define _BIGFLOAT_

#include "../big_int/big_int.hpp"

class big_float
{

private:

	big_int _numerator;
	big_int _denominator;

public:

	// Constructors

	big_float();

	big_float(big_int numerator, big_int denominator);

	~big_float();
};

#endif // ! _BIGFLOAT_
