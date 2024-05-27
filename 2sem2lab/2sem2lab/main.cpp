#include "big_int/big_int.hpp"
#include "big_float/big_float.hpp"

#include <iostream>

using namespace std;

int main()
{   
    
    auto a = big_float("16", "1");
    auto b = big_int("2");
    auto eps = big_float("25", "1000");

    std::cout << a << " " << b << " " << eps << std::endl;

    std::cout << root(a, b, eps) << std::endl;
    
    std::cout << "AA" << std::endl;
    

    /*
    auto a = big_int(std::vector<unsigned int>({ 78u, 3805702848u, 3124292368u }));
    auto b = big_int(272);
    std::cout << a << " " << b << std::endl;
    std::cout << a / b;
    */

    /*
    auto a = big_int("4263256075262470832");
    auto b = big_int("5684341433683294443");
    std::cout << a << " " << b << std::endl;
    std::cout << a + b;
    */

    return 0;
}
