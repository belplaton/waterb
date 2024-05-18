#include "big_int/big_int.hpp"
#include "big_float/big_float.hpp"

#include <iostream>

using namespace std;

int main()
{   
    auto a = big_int("536", 10);
    auto b = big_int("12", 10);
    std::cout << pow(a, b);
    return 0;
}
