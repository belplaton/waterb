#pragma once
#include "big_int.hpp"
#include "utility.hpp"
#include <string>
#include <iostream>

std::ostream& operator << (std::ostream& stream, const big_int& other)
{
    stream << other.to_string(10);

    return stream;
}

std::istream& operator >> (std::istream& stream, big_int& number)
{
    auto input = std::string();
    stream >> input;

    auto is_negative = input.size() > 0 && (input[0] == '-');
    auto valid_input = true;

    for (int i = is_negative; i < input.size(); i++)
    {
        if (!std::isdigit(input[i]))
        {
            valid_input = false;
            break;
        }
    }

    if (!valid_input)
    {
        stream.setstate(std::ios::failbit);
        return stream;
    }

    number = big_int(input, 10);
    
    return stream;
}