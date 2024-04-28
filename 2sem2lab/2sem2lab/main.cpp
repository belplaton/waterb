#include "big_int.hpp"
#include "io_operators.hpp"
#include "arithmetic_operators.hpp"
#include "assigment_operators.hpp"
#include <iostream>

using namespace std;

int main()
{

    auto digits1 = vector<unsigned int>({ 11 });
    auto value1 = big_int(digits1);

    auto digits2 = vector<unsigned int>({ 1 });
    auto value2 = big_int(digits2);

    value2 += value1;

    auto value3 = big_int("110", 2);

    std::cout << value3 << std::endl;
    return 0;
}
