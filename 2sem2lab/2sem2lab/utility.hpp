#pragma once

#include "big_int.hpp"
#include "external_utility.hpp"

std::string big_int::to_string(unsigned int base) const
{
    if (base < 2 || base > 36)
    {
        throw std::invalid_argument("Invalid base.");
    }

    std::string temp = "1";
    std::string result = "";

    for (auto i = 0; i < _digits.size(); i++)
    {
        for (auto j = 0; j < uint_size - (_digits.size() - i - 1 == 0); j++)
        {
            if (get_bit(_digits[_digits.size() - i - 1], j) == 1)
            {
                result = add_string_nums(result, temp, base);
            }

            temp = add_string_nums(temp, temp, base);
        }
    }

    return (is_negate(_digits) ? "-" : "") + result;
}

unsigned int big_int::check_for_size_change(std::vector<unsigned int> first, std::vector<unsigned int> second, bool isSum, unsigned int first_offset = 0, unsigned int second_offset = 0) const
{
    int max_size = std::max(first.size(), second.size());

    for (auto i = 0; i < max_size; i++)
    {
        auto is_finish = false;
        for (auto j = 1; j < big_int::uint_size; j++)
        {
            auto op1 = (i < first.size()) ? big_int::get_bit(first[i + first_offset], big_int::uint_size - j - (i == 0)) : 0;
            auto op2 = (i < second.size()) ? big_int::get_bit(second[i + second_offset], big_int::uint_size - j - (i == 0)) : 0;

            if (isSum)
            {
                if (!op1 && !op2)
                {
                    is_finish = true;
                    break;
                }
                else if (op1 && op2)
                {
                    max_size++;
                    is_finish = true;
                    break;
                }
            }
            else
            {
                if (op1 && !op2)
                {
                    is_finish = true;
                    break;
                }
                else if (!op1 && op2)
                {
                    is_finish = true;
                    break;
                }
                else if (op1 && op2)
                {
                    max_size--;
                    is_finish = true;
                    break;
                }
            }
        }

        if (is_finish) break;
    }

    return std::max(1, max_size);
}