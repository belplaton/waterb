#include "big_int/big_int.hpp"
#include "big_float/big_float.hpp"
#include "linked_list/linked_list.hpp" 

#include <iostream>

using namespace std;

int main()
{   
    
    auto lst = linked_list<big_int>();
    auto ll = linked_list<big_int>();
    auto a1 = big_int("-142515");
    auto a2 = big_int("124124");

    std::cout << lst << " " << lst.get_length() << std::endl;
    lst.add_value(a1);
    std::cout << lst << " " << lst.get_length() << std::endl;
    lst.remove(a2);
    std::cout << lst << " " << lst.get_length() << std::endl;
    lst.add_value(a2);
    std::cout << lst << " " << lst.get_length() << std::endl;
    lst.remove_at(0);
    std::cout << lst << " " << lst.get_length() << std::endl;

    ll.add_value(big_int("84572"));
    auto owo = big_int("1272");
    ll.add_value(owo);
    ll.add_value(big_int("9125"));

    auto g = ll + lst;
    std::cout << ll << std::endl;

    std::cout << g << std::endl;

    g -= linked_list<big_int>(std::vector<big_int>({owo}));

    std::cout << g << std::endl;
    return 0;
}
