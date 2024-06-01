#include "big_int/big_int.hpp"
#include "big_float/big_float.hpp"
#include "linked_list/linked_list.hpp"
#include "polynomial/polynomial.hpp"

#include <iostream>

using namespace std;

int main()
{   
    
    std::shared_ptr<polynomial> pol = std::make_shared<polynomial>(polynomial());
    std::shared_ptr<polynomial> pol2 = std::make_shared<polynomial>(polynomial());
    std::cout << "A" << std::endl;
    *pol += big_float(6, 7);
    std::cout << "A" << std::endl;
    *pol *= big_float(6, 7);
    std::cout << "A" << std::endl;
    *pol -= big_float(2, 4);
    std::cout << "A" << std::endl;

    auto kk = linked_list<big_float>();

    kk.add_value(4125);
    kk.add_value(big_float(7231, 255));
    kk.add_value(big_float(1262782, 623));
    kk.add_value(-1251);

    auto a = false;
    for (auto& s : kk)
    {
        if (a) *pol *= s;
        else *pol -= s;
        a = !a;
    };

    *pol2 += big_float(123, 61);
    *pol2 *= big_float(15, 156);
    *pol2 -= big_float(1251, 1723);
    *pol2 /= big_float(123515, 123515123);
    *pol2 *= big_float(15, 156);

    std::cout << *pol << std::endl;
    std::cout << "aaaa" << std::endl;
    std::cout << *pol2 << std::endl;
    std::cout << "aaaa" << std::endl;

    *pol -= *pol2;

    std::cout << *pol << std::endl;
    std::cout << "aaaa" << std::endl;

    auto pol3 = polynomial();

    std::cin >> pol3;

    std::cout << "aaa444a" << std::endl;

    std::cout << pol3 << std::endl;

    return 0;
}
