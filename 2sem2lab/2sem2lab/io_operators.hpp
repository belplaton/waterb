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

    // Проверяем, является ли введенная строка числом
    bool valid_input = true;
    for (char ch : input)
    {
        if (!std::isdigit(ch))
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