#include "big_int/big_int.hpp"
#include "big_float/big_float.hpp"

#include <iostream>

using namespace std;

int main()
{   
    auto a = big_float("256", "2");
    auto b = big_int("2");
    auto eps = big_float("1", "1000");

    std::cout << a << " " << b << " " << eps << std::endl;

    std::cout << root(a, b, eps) << std::endl;
    return 0;
}
