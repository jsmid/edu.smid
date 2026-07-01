#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

void section(const char* title) {
    cout << "\n=== " << title << " ===\n";
}

/*
Variadic templates (C++11)
=========================
A variadic template is a template that accepts a variable number of template
arguments. This solves the old C-style variadic problem (printf-style) while
keeping strong compile-time type checking.

Core syntax:
- typename... Ts      -> template parameter pack (types)
- Ts... args          -> function parameter pack (values)
- sizeof...(Ts)       -> number of elements in a pack

A common C++11 pattern is recursion with:
1) base case overload
2) recursive overload that peels one argument
*/

// -----------------------------------------------------------------------------
// 1) Count how many arguments were passed
// -----------------------------------------------------------------------------

// No recursive overload needed here: sizeof... gives the count directly.
template <typename... Ts>
std::size_t count_args(Ts... /*unused*/) {
    return sizeof...(Ts);
}

// -----------------------------------------------------------------------------
// 2) Print all arguments with recursive expansion
// -----------------------------------------------------------------------------

// Base case: no argument left.
void print_all() {
    cout << "(end)" << endl;
}

// Recursive case: print one argument, then recurse on the rest.
template <typename T, typename... Rest>
void print_all(const T& first, const Rest&... rest) {
    cout << first;
    if (sizeof...(rest) > 0) {
        cout << ", ";
    }
    print_all(rest...);
}

// -----------------------------------------------------------------------------
// 3) Sum all numeric arguments
// -----------------------------------------------------------------------------

// Base case for one value.
template <typename T>
T sum_all(T v) {
    return v;
}

// Recursive case: add first + sum(the remaining pack).
// This overload requires at least 2 arguments, so recursion eventually
// lands on the one-argument base case above.
// We use std::common_type in C++11 to compute a stable numeric result type.
template <typename T1, typename T2, typename... Rest>
typename std::common_type<T1, T2, Rest...>::type sum_all(T1 first, T2 second, Rest... rest) {
    typedef typename std::common_type<T1, T2, Rest...>::type result_t;
    return static_cast<result_t>(first) + static_cast<result_t>(sum_all(second, rest...));
}

// -----------------------------------------------------------------------------
// 4) Build a CSV string from mixed values
// -----------------------------------------------------------------------------

void append_csv(std::ostringstream& /*oss*/) {
    // Base case: nothing more to append.
}

template <typename T, typename... Rest>
void append_csv(std::ostringstream& oss, const T& first, const Rest&... rest) {
    oss << first;
    if (sizeof...(rest) > 0) {
        oss << ",";
    }
    append_csv(oss, rest...);
}

template <typename... Ts>
std::string make_csv(const Ts&... values) {
    std::ostringstream oss;
    append_csv(oss, values...);
    return oss.str();
}

// -----------------------------------------------------------------------------
// 5) Perfect forwarding example (advanced C++11 use)
// -----------------------------------------------------------------------------

/*
This pattern appears in factory helpers and container wrappers.
Args&&... here are forwarding references (in templates).
std::forward keeps lvalues as lvalues and rvalues as rvalues.
*/
template <typename T, typename... Args>
T make_object(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

struct Point {
    int x;
    int y;

    Point(int x_, int y_) : x(x_), y(y_) {}
};

int main() {
    section("1) Why variadic templates");
    cout << "Type-safe variable argument lists at compile time." << endl;
    cout << "count_args(1, 2.5, \"hello\") = " << count_args(1, 2.5, "hello") << endl;

    section("2) Recursive pack processing");
    cout << "print_all(10, 3.14, \"abc\", true): ";
    print_all(10, 3.14, "abc", true);

    section("3) Numeric aggregation");
    cout << "sum_all(1, 2, 3, 4) = " << sum_all(1, 2, 3, 4) << endl;
    cout << "sum_all(1.5, 2, 3.25) = " << sum_all(1.5, 2, 3.25) << endl;

    section("4) Mixed-type utility");
    std::string csv = make_csv("Alice", 95, "A", 2026);
    cout << "make_csv(\"Alice\", 95, \"A\", 2026) -> " << csv << endl;

    section("5) Perfect forwarding");
    Point p = make_object<Point>(10, 20);
    cout << "Point from make_object: (" << p.x << ", " << p.y << ")" << endl;

    section("6) What C++11 cannot do elegantly yet");
    cout << "C++11 often needs recursive patterns for packs." << endl;
    cout << "C++17 introduced fold expressions, e.g. (args + ...), which are shorter." << endl;

    // Compile-time checks.
    static_assert(std::is_same<decltype(sum_all(1, 2, 3)), int>::value,
                  "sum_all with ints should return int");
    static_assert(std::is_same<decltype(sum_all(1.0, 2, 3)), double>::value,
                  "mixed sum should promote to double");

    section("Summary");
    cout << "Variadic templates let you write one type-safe template for N arguments." << endl;
    cout << "In C++11, the classic technique is base case + recursive case." << endl;
    cout << "They are foundational for modern generic programming utilities." << endl;

    return 0;
}
