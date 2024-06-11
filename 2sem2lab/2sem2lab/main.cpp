#include "big_int/big_int.hpp"
#include "big_float/big_float.hpp"
#include "linked_list/linked_list.hpp"
#include "polynomial/polynomial.hpp"
#include "polynomial/polynomial_calc.hpp"
#include "linear_algebra/linear_algebra.hpp"

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    /*
    auto a = big_int("36893488147419103232");
    auto b = big_int("36893488147419013110");
    
    std::cout << a + b << std::endl;
    */

    /*
    auto a = big_float("32000");
    auto eps = big_float("1/10000");

    std::cout << a << std::endl;
    auto b = root(a, 2, eps);
    std::cout << b << std::endl;
    */
    
    
    auto file_path = std::string("calc_data.txt");
    auto calc = polynomial_calc_parser(file_path);
  
    while (calc.check_next())
    {
        auto result = calc.parse_line();
        if (result != "") std::cout << result << std::endl;
    }
    
    auto eps = big_float("1/10");
    auto a = linear_vector("[1/1, 2/1, 3/1]");
    auto b = linear_vector("[7/1, 8/1, 9/1]");
    auto c = linear_vector("[5/1, 6/1, 2/1]");
    auto h = linear_vector("[8/1, 16/1, 32/1]");
    auto d = matrix({a, b, c});
    std::cout << d << std::endl;

    auto k = linear_algebra::gram_schmidt(d, eps);
    std::cout << k << std::endl;

    auto l = linear_algebra::mixed_product(a, {b, c});
    std::cout << l << std::endl;
    auto kkk = big_float("5");


    auto n = d.invert();
    std::cout << n << std::endl;

    auto s = linear_algebra::jordan_gauss(d, h);
    std::cout << s << std::endl;

    auto o = linear_algebra::eigen_values(d, eps);
    std::cout << o << std::endl;
    
    

    return 0;
}