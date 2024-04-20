#pragma once

#include "big_int.hpp"
#include <iostream>

std::ostream& operator << (std::ostream& stream, const big_int& other)
{
    if (other.is_negate())
    {
        stream << '-';
    }

    stream << '{' << (other._digits[0] & ~other.sign_bit_mask) << '}';

    for (auto i = 1; i < other._digits.size(); i++)
    {
        stream << '{' << other._digits[i] << '}';
    }

    return stream;
}