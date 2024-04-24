#pragma once

#include "big_int.hpp"
#include <cmath>

struct sum_with_carry
{
    unsigned int sum;
    unsigned int carry;
};

struct diff_with_borrow
{
    unsigned int diff;
    unsigned int borrow;
};

sum_with_carry add_with_carry(unsigned int a, unsigned int b, unsigned int carry)
{
    auto result = sum_with_carry();
    unsigned int sum = a ^ b ^ carry;
    unsigned int remain = ((a & b) | (a & carry) | (b & carry)) << 1;

    while (remain != 0)
    {
        unsigned int temp = sum;
        sum ^= remain;
        remain = (temp & remain) << 1;
    }

    result.sum = sum;

    if ((sum < a || sum < b || sum < carry))
    {
        result.carry = 1;
    }

    return result;
}

diff_with_borrow substract_with_borrow(unsigned int a, unsigned int b, unsigned int borrow)
{
    auto result = diff_with_borrow();
    result.diff = a - b - borrow;

    if (result.diff > a)
    {
        result.borrow = 1;
    }

    return result;
}

unsigned int check_for_size_change( std::vector<unsigned int> first, std::vector<unsigned int> second, bool isSum, unsigned int first_offset = 0, unsigned int second_offset = 0)
{
    auto max_size = std::max(first.size(), second.size());

    for (auto i = 0; i < max_size; i++)
    {
        auto is_finish = false;
        for (auto j = 1; j < big_int::uint_size; j++)
        {
            auto op1 = (i < first.size()) ? big_int::get_bit(first[i + first_offset], big_int::uint_size - j - (i == 0)) : 0;
            auto op2 = (i < second.size()) ? big_int::get_bit(second[i + second_offset], big_int::uint_size - j - (i == 0)) : 0;

            if (op1 && !op2)
            {
                is_finish = true;
                break;
            }
            else if (op1 && op2)
            {
                if (isSum)
                {
                    max_size++;
                }
                else
                {
                    max_size--;
                }

                is_finish = true;
                break;
            }
        }

        if (is_finish) break;
    }

    return max_size;
}

unsigned int char_to_int(char ch, size_t base)
{
    return std::stoi(std::string(1, ch), nullptr, base);
}

char int_to_char(unsigned int num)
{
    auto first_diff = ('9' - '0') + 1;
    auto second_diff = ('Z' - 'A') + 1;

    if ((num + '0' >= '0') && (num + '0' <= '9'))
    {
        return num + '0';
    }
    else if ((num + 'A' - first_diff >= 'A') && (num + 'A' - first_diff <= 'Z'))
    {
        return num + 'A' - first_diff;
    }
    else
    {
        throw std::invalid_argument("Base is out of range (1, " + std::to_string(first_diff + second_diff) + ")");
    }
}

std::string add_string_nums(std::string& a, std::string& b, size_t base)
{
    std::string left = a.size() < b.size() ? a : b;
    std::string right = a.size() < b.size() ? b : a;

    auto max_size = std::max(a.size(), b.size()) + 1;
    std::string result = std::string(max_size, '0');

    auto op1 = 0;
    auto op2 = 0;
    auto carry = 0;
    for (auto i = 0; i < max_size; i++)
    {
        op1 = i < a.size() ? char_to_int(a[a.size() - i - 1], base) : 0;
        op2 = i < b.size() ? char_to_int(b[b.size() - i - 1], base) : 0;

        if (op1 + op2 + carry > base - 1)
        {
            result[max_size - i - 1] = int_to_char(op1 + op2 + carry - base);
            carry = 1;
        }
        else
        {
            result[max_size - i - 1] = int_to_char(op1 + op2 + carry);
            carry = 0;
        }
    }

    std::string temp(result);
    for (auto i = 0; i < max_size; i++)
    {
        if (temp[i] != '0')
        {
            break;
        }

        result.erase(0, 1);
    }

    return result;
}

std::string big_int::to_string(unsigned int base) const
{
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

    return (is_negate(_digits) && base > 2 ? "-" : "") + result;
}