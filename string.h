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
        static const std::size_t npos = -1;
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
        bool ends_with(const string& suffix) const;
        bool contains(const string& needle) const;
        std::size_t find(const string& needle, std::size_t start) const;
        string substr(std::size_t start, std::size_t length) const;
        string substr(std::size_t start) const;
        char& at(std::size_t index);
        const char& at(std::size_t index) const;
        char& front();
        const char& front() const;
        char& back();
        const char& back() const;
        void append(const string& s);
        void append(const std::string& s);
        void append(const char* s);
        void append(char c);

    };
}

#endif