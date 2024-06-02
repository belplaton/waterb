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
    auto file_path = std::string("calc_data.txt");
    auto calc = polynomial_calc_parser(file_path);
  
    while (calc.check_next())
    {
        auto result = calc.parse_line();
        if (result != "") std::cout << result << std::endl;
    }
    

    auto a = linear_vector(std::vector<big_float>({ 5, 3, 7}));
    auto b = linear_vector("[7/1, 8/1, 9/1]");
    auto c = linear_vector("[5/1, 6/1, 2/1]");
    auto d = linear_algebra::mixed_product(a, std::vector<linear_vector>({ b, c }));
    std::cout << d << std::endl;


    auto kkk = big_float("5");
    auto eps = big_float("1/10");

    auto n = logn(kkk, eps);
    std::cout << n;

    return 0;
}