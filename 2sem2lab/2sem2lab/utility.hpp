#pragma once

struct sum_with_carry
{
    unsigned int sum;
    unsigned int carry;
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
