#pragma once
#ifndef _EXUTILITY_
#define _EXUTILITY_

static struct sum_with_carry
{
    unsigned int sum;
    unsigned int carry;
};

static struct diff_with_borrow
{
    unsigned int diff;
    unsigned int borrow;
};

static sum_with_carry add_with_carry(unsigned int a, unsigned int b, unsigned int carry)
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

static diff_with_borrow substract_with_borrow(unsigned int a, unsigned int b, unsigned int borrow)
{
    auto result = diff_with_borrow();
    result.diff = a - b - borrow;

    if (result.diff > a)
    {
        result.borrow = 1;
    }

    return result;
}

static unsigned int char_to_int(char ch, size_t base)
{
    return std::stoi(std::string(1, ch), nullptr, base);
}

static char int_to_char(unsigned int num)
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

static std::string add_string_nums(std::string& a, std::string& b, size_t base)
{
    std::string left = a.size() < b.size() ? a : b;
    std::string right = a.size() < b.size() ? b : a;

    auto max_size = std::max(a.size(), b.size()) + 1;
    std::string result = std::string(max_size, '0');

    auto op1 = 0u;
    auto op2 = 0u;
    auto carry = 0u;
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

    return result != "" ? result : "0";
}

static std::string mult_string_nums(std::string& a, std::string& b, size_t base)
{
    auto max_size = a.size() + b.size();
    std::string result(max_size, '0');

    for (auto i = 0; i < a.size(); i++)
    {
        auto carry = 0u;
        for (auto j = 0; j < b.size(); j++)
        {
            auto op1 = char_to_int(a[a.size() - i - 1], base);
            auto op2 = char_to_int(b[b.size() - j - 1], base);
            auto k = (a.size() - i - 1) + (b.size() - j - 1) + 1;
            auto product = op1 * op2 + char_to_int(result[k], base) + carry;
            result[k] = int_to_char(product % base);
            carry = product / base;
        }

        result[a.size() - i - 1] = int_to_char(carry);
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

    return result != "" ? result : "0";
}

static std::string int_to_string(unsigned int num, unsigned int base)
{
    if (base < 2 || base > 36)
    {
        throw std::invalid_argument("Invalid base.");
    }

    std::string result = "";

    do
    {
        result = int_to_char(num % base) + result;
        num /= base;
    } while (num != 0);

    return result != "" ? result : "0";
}

static std::string convert_string_num(const std::string& num, unsigned int from_base, unsigned int to_base)
{
    if (from_base < 2 || from_base > 36)
    {
        throw std::invalid_argument("Invalid from_base.");
    }

    if (to_base < 2 || to_base > 36)
    {
        throw std::invalid_argument("Invalid to_base.");
    }

    int is_negative = (num[0] == '-');
    std::string result = "0";
    std::string temp = "1";
    std::string one_str = "1";
    for (auto i = 0; i < num.size() - is_negative; i++)
    {
        auto current = int_to_string(char_to_int(num[num.size() - i - 1], from_base), to_base);
        auto a = mult_string_nums(current, temp, to_base);
        auto b = int_to_string(to_base - 1, to_base);
        auto c = add_string_nums(b, one_str, to_base);

        result = add_string_nums(result, a, to_base);
        temp = mult_string_nums(temp, c, to_base);
    }

    return (is_negative ? "-" : "") + result;
}

#endif