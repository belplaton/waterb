#include "big_int/big_int.hpp"
#include "big_float/big_float.hpp"

#include <iostream>

using namespace std;

int main()
{   
    
    auto a = big_float("16", "1");
    auto b = big_float("-1/2");
    auto eps = big_float("1", "10");

    std::cout << a << " " << b << " " << eps << std::endl;

    std::cout << pow(a, b, eps) << std::endl;
    
    std::cout << "AA" << std::endl;
    

    /*
    auto a = big_float("-15617/508");
    auto b = big_float("-127/2");

    auto c = a - b;
    std::cout << a << " " << b << " " << c << std::endl;
    */

    /*
    auto a = big_int(std::vector<unsigned int>({ 2147483660u, 2018450686u }));
    auto b = big_int(std::vector<unsigned int>({ 0, 4030185488u }));

    std::cout << -a << " " << b << std::endl;

    std::cout << a % -b << std::endl;
    */

    /*
    auto a = big_int("3347378639");
    auto b = big_int("4030185488");

    std::cout << a << " " << b << std::endl;

    std::cout << a * b << std::endl;
    */

    return 0;
}
