#include "big_int/big_int.hpp"
#include "big_int/io_operators.hpp"
#include "big_int/arithmetic_operators.hpp"
#include "big_int/binary_operators.hpp"
#include <iostream>

using namespace std;

int main()
{   
    /*
    big_int value1;
    std::cin >> value1;

    big_int value2;
    std::cin >> value2;

    auto res = (value1 / value2);


    std::cout << res << " " << std::endl;
    */

    while (true)
    {
        big_int value1;
        cin >> value1;

        big_int value2;
        cin >> value2;

        auto res = (value1 / value2);

        cout << value1 << " / " << value2 << " = " << res << " " << endl << endl;
    }

    return 0;
}
