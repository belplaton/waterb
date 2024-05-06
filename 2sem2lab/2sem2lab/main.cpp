#include "big_int/big_int.hpp"
#include "big_int/io_operators.hpp"
#include "big_int/arithmetic_operators.hpp"
#include "big_int/binary_operators.hpp"
#include <iostream>

using namespace std;

int main()
{
    big_int value1;
    std::cin >> value1;

    big_int value2;
    std::cin >> value2;

    std::cout << value1 % value2 << std::endl;
    return 0;
}
