#pragma once
#ifndef _BIGINT_
#define _BIGINT_

#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include "external_utility.hpp"

class big_int
{

private:

    std::vector<unsigned int> _digits;

public:

    const size_t static uint_size = (sizeof(unsigned int) * 8);
    const unsigned int static sign_bit_mask = 1 << (uint_size - 1);

#pragma region Constructors

    big_int()
    {
        _digits = std::vector<unsigned int>(1);
    }

    big_int(int digit)
    {
        _digits = std::vector<unsigned int>(1);
        _digits[0] = digit < 0 ? -digit : digit;
        if (digit < 0) _digits[0] |= sign_bit_mask;
    }

    big_int(unsigned int digit)
    {
        _digits = std::vector<unsigned int>(1);
        _digits[0] = digit;
    }

    big_int(const unsigned int* digits, unsigned int size)
    {
        unsigned int real_size = 1;
        unsigned int diff = 0;
        auto is_negative = is_negate(digits);

        for (auto i = 0; i < size; i++)
        {
            if (i == 0 && ((digits[i] & ~sign_bit_mask) == 0))
            {
                continue;
            }

            if (digits[i] != 0)
            {
                auto bit = get_bit(digits[i], big_int::uint_size - 1);
                real_size = size - i + (!is_negative & bit);
                diff = i - (!is_negative & bit);
                break;
            }
        }

        _digits = std::vector<unsigned int>(real_size);
        for (auto i = 0; i < real_size; i++)
        {
            auto op = digits[i + diff];
            if (i + diff == 0) op &= ~sign_bit_mask;
            _digits[i] = op;
        }

        _digits[0] |= sign_bit_mask * is_negative;
    }

    big_int(const std::vector<unsigned int>& digits)
    {
        unsigned int real_size = 1;
        unsigned int diff = 0;
        auto is_negative = is_negate(digits);

        for (auto i = 0; i < digits.size(); i++)
        {
            if (i == 0 && ((digits[i] & ~sign_bit_mask) == 0))
            {
                continue;
            }

            if (digits[i] != 0)
            {
                auto bit = get_bit(digits[i], big_int::uint_size - 1);
                real_size = digits.size() - i + (!is_negative & bit);
                diff = i - (!is_negative & bit);
                break;
            }
        }

        _digits = std::vector<unsigned int>(real_size);
        for (auto i = 0; i < real_size; i++)
        {
            auto op = digits[i + diff];
            if (i + diff == 0) op &= ~sign_bit_mask;
            _digits[i] = op;
        }

        _digits[0] |= sign_bit_mask * is_negative;
    }

    big_int(const std::string& number, unsigned int base)
    {
        if (base < 2 || base > 36)
        {
            throw std::invalid_argument("Invalid base.");
        }

        int is_negative = (number[0] == '-');

        for (auto i = is_negative; i < number.size(); i++)
        {
            if (!isdigit(number[i]) && !isalpha(number[i]))
            {
                throw std::invalid_argument("Invalid character in number");
            }
        }

        auto dec_string = from_base_to_dec(number, base);
        auto bin_string = from_dec_to_base(dec_string, 2);

        auto temp = (bin_string.size() - (bin_string.size() % big_int::uint_size)) / big_int::uint_size;
        auto size = temp + 1;
        _digits = std::vector<unsigned int>(size);

        auto k = 0;
        for (auto i = 0; i < size; i++)
        {
            for (auto j = 0; j < big_int::uint_size && j < bin_string.size(); j++)
            {
                auto bit = char_to_int(bin_string[bin_string.size() - k - 1], 2);
                _digits[size - i - 1] |= (bit << j);
                k++;

                if (k == (bin_string.size() - is_negative)) break;
            }

            if (k == (bin_string.size() - is_negative)) break;
        }

        _digits[0] |= sign_bit_mask * is_negative;
    }

    big_int(const std::string& number)
    {
        int is_negative = (number[0] == '-');

        for (auto i = is_negative; i < number.size(); i++)
        {
            if (!isdigit(number[i]))
            {
                throw std::invalid_argument("Invalid character in number");
            }
        }

        auto bin_string = from_dec_to_base(number, 2);

        auto temp = (bin_string.size() - (bin_string.size() % big_int::uint_size)) / big_int::uint_size;
        auto size = temp + 1;
        _digits = std::vector<unsigned int>(size);

        auto k = 0;
        for (auto i = 0; i < size; i++)
        {
            for (auto j = 0; j < big_int::uint_size && j < bin_string.size(); j++)
            {
                auto bit = char_to_int(bin_string[bin_string.size() - k - 1], 2);
                _digits[size - i - 1] |= (bit << j);
                k++;

                if (k == (bin_string.size() - is_negative)) break;
            }

            if (k == (bin_string.size() - is_negative)) break;
        }

        _digits[0] |= sign_bit_mask * is_negative;
    }

    big_int(const big_int& other)
    {
        _digits = std::vector<unsigned int>(other._digits);
    }

    ~big_int()
    {

    }

#pragma endregion

#pragma region Relational Operators

    bool operator == (const big_int& other) const
    {
        if (_digits.size() != other._digits.size()) return false;

        for (auto i = 0; i < _digits.size(); i++)
        {
            auto op1 = _digits[i];
            if (i == 0) op1 &= ~big_int::sign_bit_mask;

            auto op2 = other._digits[i];
            if (i == 0) op2 &= ~big_int::sign_bit_mask;

            if (op1 != op2) return false;
        }

        return true;
    }

    bool operator != (const big_int& other) const
    {
        return !(*this == other);
    }

    bool operator < (const big_int& other) const
    {

        if (big_int::is_negate(*this) && !big_int::is_negate(other)) return true;
        else if (!big_int::is_negate(*this) && big_int::is_negate(other)) return false;

        if (_digits.size() < other._digits.size()) return !big_int::is_negate(*this);
        else if (_digits.size() > other._digits.size()) return big_int::is_negate(*this);

        for (auto i = 0; i < _digits.size(); i++)
        {
            auto op1 = _digits[i];
            if (i == 0) op1 &= ~sign_bit_mask;

            auto op2 = other._digits[i];
            if (i == 0) op2 &= ~sign_bit_mask;

            if (op1 < op2) return !big_int::is_negate(*this);
            else if (op1 > op2) return big_int::is_negate(*this);
        }

        return false;
    }

    bool operator <= (const big_int& other) const
    {
        return *this < other || *this == other;
    }

    bool operator > (const big_int& other) const
    {
        return !(*this <= other);
    }

    bool operator >= (const big_int& other) const
    {
        return *this > other || *this == other;
    }

#pragma endregion

#pragma region Arithmetic Operators

    big_int operator + () const
    {
        return *this;
    }

    big_int operator - () const
    {
        auto temp(*this);
        temp._digits[0] ^= sign_bit_mask;

        return temp;
    }

    big_int operator + (const big_int& other) const
    {
        auto temp = big_int(*this);
        temp += other;

        return temp;
    }

    big_int operator - (const big_int& other) const
    {
        auto temp = big_int(*this);
        temp -= other;

        return temp;
    }

    big_int operator * (const big_int& other) const
    {
        auto temp = big_int(*this);
        temp *= other;

        return temp;
    }

    big_int operator / (const big_int& other) const
    {
        auto temp = big_int(*this);
        temp /= other;

        return temp;
    }

    big_int operator % (const big_int& other) const
    {
        auto temp = big_int(*this);
        temp %= other;

        return temp;
    }

#pragma endregion

#pragma region Binary Arithmetic Operators

    big_int operator ~ () const
    {
        auto digits = std::vector<unsigned int>(_digits.size());
        for (auto i = 0; i < _digits.size(); i++)
        {
            digits[i] = (~_digits[i]);
        }

        return big_int(digits);
    }

    big_int operator & (const big_int& other) const
    {
        auto temp = big_int(*this);
        temp &= other;

        return temp;
    }

    big_int operator | (const big_int& other) const
    {
        auto temp = big_int(*this);
        temp |= other;

        return temp;
    }
    big_int operator ^ (const big_int& other) const
    {
        auto temp = big_int(*this);
        temp ^= other;

        return temp;
    }

    big_int operator << (unsigned int shift) const
    {
        auto temp = big_int(*this);
        temp <<= shift;

        return temp;
    }

    big_int operator >> (unsigned int shift) const
    {
        auto temp = big_int(*this);
        temp >>= shift;

        return temp;
    }


#pragma endregion

#pragma region Arithmetic Assigment Operators

    big_int& operator += (const big_int& other)
    {
        auto left = *this;
        auto right = other;

        // Оптимизирование
        if (is_negate(_digits) && !is_negate(other._digits))
        {
            return *this = (right - (-left));
        }
        else if (!is_negate(_digits) && is_negate(other._digits))
        {
            return *this = (left -= (-right));
        }

        auto max_size = std::max(_digits.size(), other._digits.size());
        auto result_digits = std::vector<unsigned int>(max_size);
        unsigned int carry = 0;
        for (unsigned int i = 0; i < max_size; i++)
        {
            auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
            if (i == _digits.size() - 1) op1 &= ~sign_bit_mask;

            auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;
            if (i == other._digits.size() - 1) op2 &= ~sign_bit_mask;

            auto result = add_with_carry(op1, op2, carry);

            carry = result.carry;
            result_digits[max_size - i - 1] = result.sum;
        }

        result_digits[0] |= sign_bit_mask * is_negate(_digits);
        *this = big_int(result_digits); // cuz constructor can fix representation

        return *this;
    }

    big_int& operator -= (const big_int& other)
    {
        auto left = *this;
        auto right = other;


        // Оптимизирование
        if (is_negate(left) && !is_negate(right))
        {
            return *this = (left += -right);
        }
        else if (!is_negate(left) && is_negate(right))
        {
            return *this = left += -right;
        }
        else if (is_negate(left))
        {
            if (left < right)
            {
                return *this = -(-left - -right);
            }
            else
            {
                return *this = -right - -left;
            }
        }
        else if (left < right)
        {
            return *this = -(right - left);
        }

        auto max_size = std::max(_digits.size(), other._digits.size()) + 1;
        auto result_digits = std::vector<unsigned int>(max_size);
        unsigned int borrow = 0;
        for (unsigned int i = 0; i < max_size; i++)
        {
            auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
            if (i == _digits.size() - 1) op1 &= ~sign_bit_mask;

            auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;
            if (i == other._digits.size() - 1) op2 &= ~sign_bit_mask;

            auto result = substract_with_borrow(op1, op2, borrow);

            borrow = result.borrow;
            result_digits[max_size - i - 1] = result.diff;
        }

        result_digits[0] |= sign_bit_mask * is_negate(_digits);
        *this = big_int(result_digits); // cuz constructor can fix representation

        return *this;
    }

    big_int& operator *= (const big_int& other)
    {
        if (*this == 0 || other == 0)
        {
            *this = 0;
            return *this;
        }

        auto first_size = _digits.size() - ((_digits[0] & ~sign_bit_mask) == 0);
        auto second_size = other._digits.size() - ((other._digits[0] & ~sign_bit_mask) == 0);
        auto max_size = first_size + second_size;
        auto result_digits = std::vector<unsigned int>(max_size);
        auto k = 0ull;
        auto base = (1ull << big_int::uint_size);

        auto is_negative = big_int::is_negate(*this) ^ big_int::is_negate(other);

        for (unsigned int i = 0; i < second_size; i++)
        {
            auto carry = 0ull;
            k = max_size - i - 1;

            for (unsigned int j = 0; j < first_size; j++)
            {
                k = max_size - i - j - 1;

                auto op1 = other._digits[other._digits.size() - i - 1];
                if (i == other._digits.size() - 1) op1 &= ~sign_bit_mask;

                auto op2 = _digits[_digits.size() - j - 1];
                if (j == _digits.size() - 1) op2 &= ~sign_bit_mask;

                auto temp = (static_cast<unsigned long long>(op1) * static_cast<unsigned long long>(op2)) + carry + result_digits[k];

                carry = temp / base;
                result_digits[k] = temp % base;
            }

            result_digits[k - 1] += carry;
        }

        result_digits[0] |= sign_bit_mask * is_negative;
        *this = big_int(result_digits); // cuz constructor can fix representation

        return *this;
    }

    big_int& operator /= (const big_int& other)
    {
        if (other == 0)
        {
            throw std::logic_error("Cant divide by zero");
        }

        if (other == 1)
        {
            return *this;
        }

        auto left = is_negate(*this) ? -*this : *this;
        auto right = is_negate(other) ? -other : other;
        auto is_negative = is_negate(*this) ^ is_negate(other);

        auto start_range = big_int();
        auto end_range = big_int(left);
        auto potential_result = big_int();
        auto result = big_int();
        auto carry = big_int();

        do
        {
            potential_result = ((start_range + end_range) >> 1);
            result = potential_result * right;
            carry = left - result;

            if (carry >= 0 && carry < right)
            {
                potential_result._digits[0] |= sign_bit_mask * is_negative;
                *this = potential_result;
                return *this;
            }

            if (result > left)
            {
                end_range = potential_result;
            }
            else
            {
                start_range = potential_result;
            }

        } while (potential_result != 0);

        throw std::logic_error("Error in divide function!");;
    }


    big_int& operator %= (const big_int& other)
    {
        if (other == 0)
        {
            throw std::logic_error("Cant divide by zero");
        }

        if (other == 1)
        {
            return *this;
        }

        auto left = is_negate(*this) ? -*this : *this;
        auto right = is_negate(other) ? -other : other;
        auto is_negative = is_negate(*this) ^ is_negate(other);

        auto start_range = big_int();
        auto end_range = big_int(left);
        auto potential_result = big_int();
        auto result = big_int();
        auto carry = big_int();

        do
        {
            //std::cout << "A" << std::endl;
            potential_result = ((start_range + end_range) >> 1);
            //std::cout << "B" << potential_result << " " << right << std::endl;
            result = potential_result * right;
            //std::cout << "C" << std::endl;
            carry = left - result;

            //std::cout << "D" << std::endl;
            std::cout << end_range << " " << start_range << " " << potential_result << " " << result << " " << carry << std::endl;
            //std::cout << std::endl;

            if (carry >= 0 && carry < right)
            {
                carry._digits[0] |= sign_bit_mask * is_negative;
                *this = carry;
                return *this;
            }

            if (result > left)
            {
                end_range = potential_result;
            }
            else
            {
                start_range = potential_result;
            }

        } while (potential_result != 0);

        throw std::logic_error("Error in divide function!");;
    }

#pragma endregion

#pragma region Binary Assigment Operators

    big_int& operator &= (const big_int& other)
    {
        auto max_size = std::max(_digits.size(), other._digits.size());
        auto digits = std::vector<unsigned int>(max_size);
        for (auto i = 0; i < max_size; i++)
        {
            auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
            auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;

            digits[max_size - i - 1] = op1 & op2;
        }

        _digits = digits;

        return *this;
    }

    big_int& operator |= (const big_int& other)
    {
        auto max_size = std::max(_digits.size(), other._digits.size());
        auto digits = std::vector<unsigned int>(max_size);
        for (auto i = 0; i < max_size; i++)
        {
            auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
            auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;

            digits[max_size - i - 1] = op1 | op2;
        }

        _digits = digits;

        return *this;
    }

    big_int& operator ^= (const big_int& other)
    {
        auto max_size = std::max(_digits.size(), other._digits.size());
        auto digits = std::vector<unsigned int>(max_size);
        for (auto i = 0; i < max_size; i++)
        {
            auto op1 = (i < _digits.size()) ? _digits[_digits.size() - i - 1] : 0;
            auto op2 = (i < other._digits.size()) ? other._digits[other._digits.size() - i - 1] : 0;

            digits[max_size - i - 1] = op1 ^ op2;
        }

        _digits = digits;

        return *this;
    }

    big_int& operator <<= (unsigned int shift)
    {
        int empty = 0;
        int macro_diff = 0;

        for (auto i = 0; i < _digits.size(); i++)
        {
            auto finished = false;
            for (auto j = 0; j < big_int::uint_size; j++)
            {
                int bit = get_bit(_digits[i], big_int::uint_size - j - 1);
                if (i == 0) bit &= ~sign_bit_mask;
                empty += bit > 0 ? 0 : 1;
                if (bit)
                {
                    int temp1 = (shift - shift % big_int::uint_size) / big_int::uint_size;
                    int temp2 = (shift % big_int::uint_size) - empty;
                    macro_diff = temp1 + (temp2 > 0 ? 1 : 0);
                    finished = true;
                    break;
                }
            }

            if (finished) break;
        }

        int size = _digits.size() + macro_diff;
        auto result_digits = std::vector<unsigned int>(size);
        for (unsigned int k = 0; k < (_digits.size() * big_int::uint_size); k++)
        {
            auto i1 = (k - k % big_int::uint_size) / big_int::uint_size;
            auto i2 = ((k + shift) - (k + shift) % big_int::uint_size) / big_int::uint_size;

            auto j1 = k % big_int::uint_size;
            auto j2 = (k + shift) % big_int::uint_size;

            auto num = i1 < _digits.size() ? _digits[_digits.size() - i1 - 1] : 0;
            if (_digits.size() - i1 - 1 == 0) num &= ~sign_bit_mask;

            auto bit = get_bit(num, j1);
            if (bit) result_digits[size - i2 - 1] |= (bit << j2);
        }


        result_digits[0] |= big_int::sign_bit_mask * is_negate(*this);
        *this = big_int(result_digits); // cuz constructor can fix representation

        return *this;
    }

    big_int& operator >>= (unsigned int shift)
    {
        int empty = 0;
        int macro_diff = 0;

        for (auto i = 0; i < _digits.size(); i++)
        {
            auto finished = false;
            for (auto j = 0; j < big_int::uint_size; j++)
            {
                int bit = get_bit(_digits[i], big_int::uint_size - j - 1);
                if (i == 0) bit &= ~sign_bit_mask;
                empty += bit > 0 ? 0 : 1;
                if (bit)
                {
                    int temp1 = (shift - shift % big_int::uint_size) / big_int::uint_size;
                    int temp2 = (shift % big_int::uint_size) - (empty);
                    macro_diff = temp1 + (temp2 > 0 ? 1 : 0);
                    finished = true;
                    break;
                }
            }

            if (finished) break;
        }

        int size = _digits.size() + macro_diff;
        auto result_digits = std::vector<unsigned int>(size);
        for (unsigned int k = 0; k < (_digits.size() * big_int::uint_size); k++)
        {
            auto i2 = (k - k % big_int::uint_size) / big_int::uint_size;
            auto i1 = ((k + shift) - (k + shift) % big_int::uint_size) / big_int::uint_size;

            auto j2 = k % big_int::uint_size;
            auto j1 = (k + shift) % big_int::uint_size;

            auto num = i1 < _digits.size() ? _digits[_digits.size() - i1 - 1] : 0;
            if (_digits.size() - i1 - 1 == 0) num &= ~sign_bit_mask;

            auto bit = get_bit(num, j1);
            if (bit) result_digits[size - i2 - 1] |= (bit << j2);
        }


        result_digits[0] |= big_int::sign_bit_mask * is_negate(*this);
        *this = big_int(result_digits); // cuz constructor can fix representation

        return *this;
    }


#pragma endregion

#pragma region  IO Operators

    friend std::ostream& operator << (std::ostream& stream, const big_int& other)
    {
        stream << other.to_string(10);

        return stream;
    }

    friend std::istream& operator >> (std::istream& stream, big_int& number)
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

#pragma endregion

#pragma region Utility

    inline static unsigned int get_bit(unsigned int num, unsigned int position)
    {
        return (num >> position) & 1;
    }

    inline static bool is_negate(const big_int& number)
    {
        return get_bit(number._digits[0], sign_bit_mask - 1);
    }

    inline static bool is_negate(const std::vector<unsigned int>& digits)
    {
        return get_bit(digits[0], sign_bit_mask - 1);
    }

    inline static bool is_negate(const unsigned int* digits)
    {
        return get_bit(digits[0], sign_bit_mask - 1);
    }

    inline static bool is_negate(unsigned int digit)
    {
        return get_bit(digit, sign_bit_mask - 1);
    }

    inline static big_int abs(const big_int& other)
    {
        if (other < 0) return big_int(-other);
        return other;
    }

    std::string to_string(unsigned int base) const
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

        if (result == "")
        {
            return "0";
        }

        return (is_negate(_digits) ? "-" : "") + result;
    }

    friend big_int gcd(const big_int& a, const big_int& b)
    {
        big_int x = big_int(a);
        big_int y = big_int(b);

        if (x == 0 || y == 1) return y;
        if (y == 0 || x == 1) return x;

        while (y != 0 && x != 1)
        {
            auto temp = x % y;
            x = y;
            y = temp;
        }

        return x;
    }

    friend big_int pow(const big_int& base, const big_int& exponent)
    {
        if (exponent < 0)
        {
            throw std::invalid_argument("Can`t pow big int in non negate exponent.");
        }

        if (exponent == 0) return 1;

        auto result = big_int(1);
        auto exp = big_int(exponent);
        auto temp = big_int(base);
        while (exp != 0)
        {
            if (exp % 2 != 0)
            {
                result = result * temp;
            }

            temp *= temp;
            exp >>= 1;
        }

        return result;
    }

#pragma endregion

};

#endif // ! _BIGINT_
