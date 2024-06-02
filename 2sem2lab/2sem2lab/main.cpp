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
    //auto file_path = std::string("calc_data.txt");
    //auto calc = polynomial_calc_parser(file_path);
  
    //while (calc.check_next())
    //{
    //    auto result = calc.parse_line();
    //    if (result != "") std::cout << result << std::endl;
    //}
    

    auto a = linear_vector(std::vector<big_float>({ 5, 3, 7, 4 }));
    auto b = linear_vector("[7/1, 8/1, 9/1, 8/1]");
    auto c = linear_vector("[5/1, 6/1, 2/1, 4/1]");
    auto d = linear_algebra::cross(std::vector<linear_vector>({ a, b, c }));
    std::cout << d << std::endl;

    return 0;
}