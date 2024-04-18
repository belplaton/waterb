#pragma once

#include "big_int.hpp"
#include <iostream>

std::ostream& operator << (std::ostream& stream, const big_int& other)
{
    for (auto digit : other._digits)
    {
        stream << '{' << digit << '}';
    }
    return stream;
}