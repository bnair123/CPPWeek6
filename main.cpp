#include <iostream>
#include "string.h"

int main() {
    cppf::string str1{"Alice"};
    cppf::string str2{std::string{"Bob"}};
    cppf::string str3{str2};
    std::cout << str1 << " and " << str2 << " are friends." << std::endl;
    std::cout << "Length of str1: " << str1.length() << std::endl;
    std::cout << "Length of str2: " << str2.length() << std::endl;
    std::cout << "Length of str3: " << str3.length() << std::endl;


    return 0;
}