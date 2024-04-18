#include "big_int.hpp"
#include "io_operators.hpp"
#include "arithmetic_operators.hpp"
#include <iostream>

using namespace std;

int main()
{
    auto digits1 = vector<unsigned int>({ (unsigned int)(1 << 31) + 1, 4294967295U, 7U, 4294967295U });
    auto value1 = big_int(digits1);

    auto digits2 = vector<unsigned int>({ 0, 78, 12 });
    auto value2 = big_int(digits2);

    std::cout << value1 + value2 << std::endl;
    return 0;
}
