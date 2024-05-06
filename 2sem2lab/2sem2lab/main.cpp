#include "big_int.hpp"
#include "io_operators.hpp"
#include "arithmetic_operators.hpp"
#include "binary_operators.hpp"
#include <iostream>

using namespace std;

int main()
{

    auto digits1 = vector<unsigned int>({ 11 });
    auto value1 = big_int(digits1);

    auto digits2 = vector<unsigned int>({ 1u, 16u + 8u + 4u + 2u });
    auto value2 = big_int(digits2);

    auto value3 = big_int("-11", 10);
    auto value4 = big_int("11", 10);


    std::cout << value3 * value4 << std::endl;
    return 0;
}
