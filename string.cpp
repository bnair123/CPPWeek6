#include "string.h"

namespace cppf {
    string::string() : str{new char[1]}, len{0} {
        str[0] = '\0';
    }

    string::string(const char* s) : str{new char[std::strlen(s) + 1]}, len{std::strlen(s)} {
        std::strcpy(str, s);
    }

    string::string(const std::string& s) : str{new char[s.size() + 1]}, len{s.size()} {
        std::strcpy(str, s.c_str());
    }

    string::~string() {
        delete[] str;
    }

    size_t string::length() const {
        return len;
    }

    const char* string::c_str() const {
        return str;
    }

    string& string::operator=(const char* s) {
        delete[] str;
        str = new char[std::strlen(s) + 1];
        std::strcpy(str, s);
        len = std::strlen(s);
        return *this;
    }

    bool string::empty() const {
        return len == 0;
    }

    const char* string::data() const {
        return str;
    }

    string& string::operator=(const string& s) {
        if (this == &s) {
            return *this;
        }
        delete[] str;
        len = s.len;
        str = new char[len + 1];
        std::strcpy(str, s.str);
        return *this;
    }


    string& string::operator+=(const char* s) {
        char* temp = new char[len + std::strlen(s) + 1];
        std::strcpy(temp, str);
        std::strcat(temp, s);
        delete[] str;
        str = temp;
        len += std::strlen(s);
        return *this;
    }

    string& string::operator+=(const string& s) {
        char* temp = new char[len + s.len + 1];
        std::strcpy(temp, str);
        std::strcat(temp, s.str);
        delete[] str;
        str = temp;
        len += s.len;
        return *this;
    }

    char& string::operator[](size_t i) {
        return str[i];
    }

    const char& string::operator[](size_t i) const {
        return str[i];
    }

    std::ostream& operator<<(std::ostream& os, const string& s) {
        os << s.str;
        return os;
    }

    string::string(const string& other) {
        len = other.length();
        str = new char[len + 1];
        std::strcpy(str, other.data());
    }


}