#include <iostream>
#include "trigger.hpp"

void sum(int a, int b) {
    std::cout << "trigger: num_i" << std::endl;
    std::cout << "num_i + b = " << a + b << std::endl;
}

int main() {

    // Tests
    
    // int
    trigger<int> num_i = 10;
    num_i.call(sum, num_i, 11);
    num_i = 19;
    std::cout << num_i << std::endl << std::endl;

    // double
    trigger<double> num_d = 0.6;
    num_d.call([]() {
        std::cout << "foo: num_d" << std::endl;
    });
    num_d = num_d + 10.5;
    std::cout << num_d << std::endl << std::endl;

    trigger<trigger<trigger<bool>>> num_b = 0;
    num_b.call([]() {
        std::cout << "foo: num_b1" << std::endl;
    });
    num_b.value.call([]() {
        std::cout << "foo: num_b2" << std::endl;
    });
    num_b.value.value.call([]() {
        std::cout << "foo: num_b3" << std::endl;
    });

    // if we put a trigger inside another trigger, then we must use explicit
    // type casting, otherwise there will be an error “does not define this
    // operator or the type conversion is acceptable to the built-in trigger
    // operator...” (I did not find another way to solve this problem)
    num_b = (double)num_b + 1;
    std::cout << num_b << std::endl << std::endl;

    // string
    trigger<std::string> str = "World";
    str.call([]() {
        std::cout << "foo: str" << std::endl;
        });
    str = "hell";
    str.value.push_back('o');
    std::cout << str << std::endl << std::endl;


    trigger<trigger<int>> obj = 1;
    obj.call([]() {
        std::cout << "foo: obj1" << std::endl;
        });
    obj.value.call([]() {
        std::cout << "foo: obj2" << std::endl;
        });
    obj = 10 + (int)obj;
    std::cout << obj << std::endl << std::endl;

    trigger<int>* ptr = &obj.value;
    ptr->call([]() {
        std::cout << "foo: ptr" << std::endl;
    });


    obj = 1;
    *ptr = 2;

	return 0;
}