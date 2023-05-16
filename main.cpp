#include <iostream>
#include "string.h"

int main() {
    cppf::string str1{"Alice"};
    std::string str2{" and Bob"};
    cppf::string str3{" friends"};
    char c = '!';

    // Use append functions
    str1.append(" and Bob");
    str1.append(str2);
    str1.append(str3);
    str1.append(c);

    // Output: Alice and Bob and Bob friends.!
    std::cout << str1 << std::endl;

    // Use substr functions
    cppf::string str4 = str1.substr(0, 5); // Alice
    cppf::string str5 = str1.substr(10); // and Bob friends.!

    // Output: Alice
    std::cout << str4 << std::endl;

    // Output: and Bob friends.!
    std::cout << str5 << std::endl;

    // Use at, front, back functions
    str1.at(0) = 'E';
    str1.back() = '?';

    // Output: Elice and Bob and Bob friends.?
    std::cout << str1 << std::endl;

    return 0;
}
