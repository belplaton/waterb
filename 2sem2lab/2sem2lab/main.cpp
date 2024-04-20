#include "big_int.hpp"
#include "io_operators.hpp"
#include "arithmetic_operators.hpp"
#include <iostream>

using namespace std;

int main()
{

    auto digits1 = vector<unsigned int>({ (unsigned int)(1 << 30) - 1, 0, 5});
    auto value1 = big_int(digits1);

    auto digits2 = vector<unsigned int>({ (unsigned int)(1 << 31), 0, 5 });
    auto value2 = big_int(digits2);

    auto b = value1 + value1;
    std::cout << b << std::endl;
    std::cout << b + value1 << std::endl;
    return 0;
}
