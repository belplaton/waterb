#pragma once
#include "big_int.hpp"
#include "utility.hpp"
#include <iostream>

std::ostream& operator << (std::ostream& stream, const big_int& other)
{
    stream << other.to_string(10);

    return stream;
}