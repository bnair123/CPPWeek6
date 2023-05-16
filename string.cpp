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

    bool string::ends_with(const string& suffix) const {
        if (suffix.len > len) {
            return false;
        }
        return std::strcmp(str + len - suffix.len, suffix.str) == 0;
    }

    bool string::contains(const string& needle) const {
        return std::strstr(str, needle.str) != nullptr;
    }

    std::size_t string::find(const string& needle, std::size_t start) const {
        if (start > len) {
            return npos;
        }
        const char* result = std::strstr(str + start, needle.str);
        if (result == nullptr) {
            return npos;
        }
        return result - str;
    }

    string string::substr(std::size_t start, std::size_t length) const {
        if (start > len) {
            throw std::out_of_range("start is out of range");
        }
        if (start + length > len) {
            length = len - start;
        }
        char* temp = new char[length + 1];
        std::strncpy(temp, str + start, length);
        temp[length] = '\0';

        string result(temp);
        delete[] temp;
        return result;
    }

    string string::substr(std::size_t start) const {
        return substr(start, len - start);
    }

// at methods
    char& string::at(std::size_t index) {
        if (index >= len) {
            throw std::out_of_range("index out of range");
        }
        return str[index];
    }

    const char& string::at(std::size_t index) const {
        if (index >= len) {
            throw std::out_of_range("index out of range");
        }
        return str[index];
    }

    char& string::front() {
        if (empty()) {
            throw std::runtime_error("empty string");
        }
        return str[0];
    }

    const char& string::front() const {
        if (empty()) {
            throw std::runtime_error("empty string");
        }
        return str[0];
    }

    char& string::back() {
        if (empty()) {
            throw std::runtime_error("empty string");
        }
        return str[len - 1];
    }

    const char& string::back() const {
        if (empty()) {
            throw std::runtime_error("empty string");
        }
        return str[len - 1];
    }

// append methods
    void string::append(const string& s) {
        operator+=(s);
    }

    void string::append(const std::string& s) {
        operator+=(s.c_str());
    }

    void string::append(const char* s) {
        operator+=(s);
    }

    void string::append(char c) {
        char temp[2] = {c, '\0'};
        operator+=(temp);
    }

}