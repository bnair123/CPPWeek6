#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <string>
#include <cstring>

namespace cppf {
    class string {
    private:
        char* str;
        size_t len;
    public:
        string();
        string(const char* s);
        explicit string(const std::string& s);
        ~string();
        size_t length() const;
        const char* c_str() const;
        string(const string& other);
        string& operator=(const char* s);
        string& operator=(const string& s);
        string& operator+=(const char* s);
        string& operator+=(const string& s);
        char& operator[](size_t i);
        const char& operator[](size_t i) const;
        friend std::ostream& operator<<(std::ostream& os, const string& s);
        bool empty() const;
        const char* data() const;

    };
}

#endif