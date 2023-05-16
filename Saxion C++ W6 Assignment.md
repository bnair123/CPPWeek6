> This assignment is done **individually**. There is one mandatory part this week.

## Part 1

Write a class `string` that offers functionality similar to that of `std::string`. `string` must be defined in a `namespace`, e.g., `cppf`. `string` uses a dynamically allocated array of `char`s for storage. This can be represented either by a raw pointer (`char*`) or by a managed pointer (`std::unique_ptr<char[]>`).

> When implementing your `string` class, you will need to decide which member functions are `const` and which are not. You will also need to decide whether to `const`-overload some of the member functions.

> You may add any `private` member functions you need to to your `string` class.

The `string` class exposes the following public functions:

### Constructors and copy assignment

-   A _default constructor_, that constructs an empty string.
-   A constructor that takes a string literal (`const char*`) as its argument and initializes a `string` object with its content.
-   A constructor that takes a `std::string` argument and initializes a `string` object with its content.
-   A _copy constructor_ that constructs a full, deep copy of another `string` object.
-   A _copy assignment operator_ that assigns a new value to an existing `string` object, making a full copy of its argument in the process.

Depending on whether you use a raw pointer or a managed pointer, you may need to implement dynamic resource clean-up in your `string` class.

```
cppf::string str0{};    // default constructor
cppf::string str1{"Alice"}; // from a string literal
cppf::string str2 = std::string{"Bob"}; // from std::string
cppf::string str3{str2};    // copy constructor
str0 = str1;    // copy assignment operator
```

### Accessors

-   `length()` that returns the number of characters in the string.
-   `empty()` — returns `true` if the string is empty.
-   `operator bool()` — returns `true` is the string is **not** empty _[optional]_.
-   `c_str()` — returns a raw, constant pointer to the storage array.
-   `data()` — returns a raw, non-constant pointer to the storage array.

```
cppf::string str{"Alice"};
std::cout << str.length(); // 5
std::cout << str.empty() << ", " << (bool)str; // 0, 1
std::cout << str.c_str();   // Alice
```

The following functions must be const-overloaded:

-   `at(std::size_t index)` that returns the character at `index`. It should throw an exception on an out-of-bounds access.
-   `operator[](std::size_t index)` — works just like `at` but doesn’t throw an exception _[optional]_.
-   `front()` that returns the first character in the string.
-   `back()` that returns the last character in the string.

```
cppf::string str{"Bob"};
str[0] = 'R';   // str is not "Rob"
str.back() = 't';   // str is not "Rot"
str.at(1) = 'a';    //str is now "Rat";
char c = str.at(100); // an exception is thrown
```

### Modifiers

-   `void append(T str)` — appends a string passed as an argument to the current instance. This function should be overloaded for the following types of argument: `string`, `std::string`, `const char*`, `char`.

```
cppf::string str{"Alice"};
str.append(" and Bob"}; // str is now "Alice and Bob"

std::string are{" are"};
str.append(are);    // str is now "Alice and Bob are"

cppf::string another{" friends."};
str.append(another};    // str is now "Alice and Bob are friends."
```

### Searching and substrings

-   `cppf::string substr(std::size_t start, std::size_t length)` — returns a substring of the current instance starting at index `start` and with the length passed as an argument.
-   `cppf::string substr(std::size_t start)` — same as above but the length is unbounded: the substring from index `start` until the end of the original string.
-   `bool starts_with(const cppf::string& prefix)` — returns `true` if the string starts with a `prefix`.
-   `bool ends_with(const cppf::string& suffix)` — returns `true` if the string ends with a `suffix`.
-   `bool contains(const cppf::string& needle)` — returns `true` if the string contains substring `needle`.
-   `std::size_t find(const cppf::string& needle)` — returns the index at which substring `needle` is found in a string or `string::npos` if the string doesn’t contain such a substring.
-   `std::size_t find(const cppf::string& needle, std::size_t start)` — same as above but starts searching at the index `start`.

To allow checking for the absence of a substring, you should define a constant `npos` in your `string` class:

```
namespace cppf {
class string {
public:
    static const std::size_t npos = -1;
    // ...
};
}
```

Example:

```
cppf::string str{"Alice and Bob have mice"};

auto alice = str.subst(0, 5); // alice contains "Alice"
auto mice = str.substr(19); // mice contains "mice"
std::cout << str.starts_with("alice");  // 0
std::cout << str.ends_with("mice"); // 1
std::cout << str.contains("b h");   // `
std::cout << str.find("ic");    // 2
std::cout << str.find("ic", 3); // 20
```

### Other (free functions)

-   A _stream output operator_ for the `cppf::string` class.

```
cppf::string str{"Alice"};
std::cout << str;   // Alice
std::cout << with_bob;  // Alice and Bob
```

**MUSTS**:

-   All the functions mentioned above that are not marked as _[optional]_ must be implemented.
-   `string` must be implemented in its own `namespace` to avoid name collision with `std::string`.
-   Compiler warnings must be enabled in the CMakelists.txt file.
-   The code must compile without warnings.

## Part 2 (optional)

### Restricted memory use

> If you decide to work on this part, create a new `class` called `rstring` in a separate file. You can use the same `namespace` as in Part 1.

Your `rstring` has to work on a platform with restricted resources. Making copies of strings is strongly discouraged. Moreover, all the instances of `rstring` can only allocate a fixed amount of memory defined as a constant in the `rstring` header:

```
// part of rstring.h

static const std::size_t MAX_ALLOCATED_SIZE{512};
```

Redesign and rewrite your class in such a way that:

-   Making copies with a _copy constructor_ and a _copy assignment operator_ is not possible.
-   There is a function `void copy_from(const rstring& other)` that performs a deep copy.
-   When the size of the memory allocated by all existing `rstring` objects exceeds `MAX_ALLOCATED_SIZE` , no more new instance can be created, unless some of it is freed. This rule is also enforced if there is still memory available but a new instance needs more bytes than can be allocated.

For the enforcement of the allocation limit you’ll need a `rstring` variable to track the memory usage of your `rstring` class. You can either throw an exception from a `rstring` constructor to prohibit a new instance construction or create an object with a `0` length (and no array allocated). If you choose the former you’ll need to signal the error to a user in some other way—for instance by having a `good` flag in the `rstring` class that’s set to `false` on error.

### Stream extraction operator

Implement a _stream extraction operator_ for your original `string` class. It should read in words from an input stream, just like in the case of `std::string`. A word is a chain of printable characters separated by whitespace characters.

```
std::string sentence{"Alice.  Bob    ,and Cindy"};
std::istringstream iss{sentence};
string str;

iss >> str; // reads in "Alice."
iss >> str  // reads in "Bob"
iss >> str  // reads in ",and"
iss >> str  // reads in "Cindy" 
```