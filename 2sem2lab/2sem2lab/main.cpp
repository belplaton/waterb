#include "big_int.hpp"
#include "io_operators.hpp"
#include "arithmetic_operators.hpp"
#include <iostream>

using namespace std;

int main()
{

    auto digits1 = vector<unsigned int>({ 11115 });
    auto value1 = big_int(digits1);

    auto digits2 = vector<unsigned int>({ 11111 });
    auto value2 = big_int(digits2);

    auto digits3 = vector<unsigned int>({ 155511 });
    auto value3 = big_int(digits3);

    std::cout << (-value2 + -value1)<< std::endl;
    return 0;
}
