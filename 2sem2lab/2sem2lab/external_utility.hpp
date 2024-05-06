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

static int compare_string_nums(const std::string& a, const std::string& b)
{
    auto first_negative = a[0] == '-';
    auto second_negative = b[0] == '-';

    auto first = a.substr(first_negative, a.size());
    auto second = b.substr(second_negative, b.size());

    if (first_negative && !second_negative)
    {
        return -1;
    }
    else if (!first_negative && second_negative)
    {
        return 1;
    }

    if (first.size() < second.size())
    {
        return -1;
    }
    else if (first.size() > second.size())
    {
        return 1;
    }

    for (size_t i = 0; i < first.size(); ++i) {
        if (first[i] < second[i]) {
            return -1;
        }
        else if (first[i] > second[i]) {
            return 1;
        }
    }

    return 0;
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

static std::string subtract_string_nums(std::string& a, std::string& b, size_t base)
{
    auto first_negative = a[0] == '-';
    auto second_negative = b[0] == '-';
    auto result_negative = first_negative ^ second_negative;

    auto first = a.substr(first_negative, a.size());
    auto second = b.substr(second_negative, b.size());

    if (compare_string_nums(first, second) == -1)
    {
        return "-" + subtract_string_nums(second, first, base);
    }

    auto max_size = first.size();
    std::string result = std::string(max_size, '0');

    auto op1 = 0u;
    auto op2 = 0u;
    auto borrow = 0;

    for (size_t i = 0; i < max_size; ++i)
    {
        op1 = i < first.size() ? char_to_int(first[first.size() - i - 1], base) : 0;
        op2 = i < second.size() ? char_to_int(second[second.size() - i - 1], base) : 0;

        int difference = op1 - op2 - borrow;

        if (difference < 0)
        {
            difference += base;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result[max_size - i - 1] = int_to_char(difference);
    }

    std::string temp(result);
    for (auto i = 0; i < temp.size(); i++)
    {
        if (temp[i] != '0')
        {
            break;
        }

        result.erase(0, 1);
    }

    if (result == "")
    {
        return "0";
    }

    return (first_negative ? "-" : "") + result;
}

static std::string mult_string_nums(std::string& a, std::string& b, size_t base)
{
    auto first_negative = a[0] == '-';
    auto second_negative = b[0] == '-';
    auto result_negative = first_negative ^ second_negative;

    auto first = a.substr(first_negative, a.size());
    auto second = b.substr(second_negative, b.size());

    auto max_size = first.size() + second.size();
    std::string result(max_size, '0');

    for (auto i = 0; i < first.size(); i++)
    {
        auto carry = 0u;
        for (auto j = 0; j < second.size(); j++)
        {
            auto op1 = char_to_int(first[first.size() - i - 1], base);
            auto op2 = char_to_int(second[second.size() - j - 1], base);
            auto k = (first.size() - i - 1) + (second.size() - j - 1) + 1;
            auto product = op1 * op2 + char_to_int(result[k], base) + carry;
            result[k] = int_to_char(product % base);
            carry = product / base;
        }

        result[first.size() - i - 1] = int_to_char(carry);
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

    if (result == "")
    {
        return "0";
    }

    return (result_negative ? "-" : "") + result;
}

static std::string div_string_nums(const std::string& a, const std::string& b, size_t base)
{
    auto first_negative = a[0] == '-';
    auto second_negative = b[0] == '-';
    auto result_negative = first_negative ^ second_negative;

    auto first = a.substr(first_negative, a.size());
    auto second = b.substr(second_negative, b.size());
    auto result = std::string("0");

    if (second == "0")
    {
        throw std::invalid_argument("Error: Division by zero");
    }

    if (compare_string_nums(first, second) == -1)
    {
        return "0";
    }

    auto str_one = std::string("1");
    auto current = std::string(second);

    while (true)
    {
        first = subtract_string_nums(first, second, base);
        if (compare_string_nums(first, "0") != -1)
        {
            result = add_string_nums(result, str_one, base);
        }
        else if (compare_string_nums(first, "0") != 1)
        {
            break;
        }
    }

    std::string temp(result);
    for (auto i = 0; i < temp.size(); i++)
    {
        if (temp[i] != '0')
        {
            break;
        }

        result.erase(0, 1);
    }

    if (result == "")
    {
        return "0";
    }

    return (result_negative ? "-" : "") + result;
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

static std::string from_base_to_dec(const std::string& num, unsigned int base)
{
    if (base < 2 || base > 36)
    {
        throw std::invalid_argument("Invalid base.");
    }

    int is_negative = (num[0] == '-');

    std::string one_str = "1";
    std::string result = "0";

    auto a = int_to_string(base - 1, 10);
    auto from_base_str = add_string_nums(a, one_str, 10);

    // Convert to decimal
    for (auto i = 0; i < num.size() - is_negative; i++)
    {
        std::string mult = "1";
        for (auto j = 0; j < i; j++)
        {
            mult = mult_string_nums(mult, from_base_str, 10);
        }

        auto a = int_to_string(char_to_int(num[num.size() - i - 1], base), 10);
        auto b = mult_string_nums(a, mult, 10);

        result = add_string_nums(result, b, 10);
    }

    return (is_negative ? "-" : "") + result;
}

static std::string from_dec_to_base(const std::string& num, unsigned int base)
{
    if (base < 2 || base > 36)
    {
        throw std::invalid_argument("Invalid base.");
    }

    int is_negative = (num[0] == '-');

    std::string one_str = "1";
    std::string result = "";
    std::string temp_num = num.substr(is_negative, num.size());
    auto temp_num_free = false;

    auto b = int_to_string(base - 1, 10);
    auto to_base_str = add_string_nums(b, one_str, 10);

    while (!temp_num_free)
    {
        auto remainder = 0;
        std::string dec = "";
        for (auto i = 0; i < temp_num.size(); i++)
        {
            auto digit = char_to_int(temp_num[i], 10);
            auto temp = digit + remainder * 10;
            dec.push_back(int_to_char(temp / base));
            remainder = temp % base;
        }

        if (result.empty() && remainder == 0)
        {
            result = "0" + result;
        }
        else
        {
            result = int_to_char(remainder) + result;
        }

        temp_num = dec;
        for (auto i = 0; i < temp_num.length(); i++)
        {
            if (temp_num[i] != '0')
            {
                temp_num_free = false;
                break;
            }

            temp_num_free = true;
        }
    }
    
    return (is_negative ? "-" : "") + result;
}

#endif