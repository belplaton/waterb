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

    auto digits2 = vector<unsigned int>({ 175u, 1123521u });
    auto value2 = big_int(digits2);

    std::cout << value1 << std::endl;
    std::cout << value2 << std::endl;

    //auto value3 = big_int("1255555666777", 10);


    std::cout << (value2 << 3) + value2 << std::endl;
    return 0;
}
