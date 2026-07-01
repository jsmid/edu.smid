/*
Keyword nullptr in C++11
========================
nullptr is a dedicated null pointer literal of type std::nullptr_t.
It replaces old NULL/0 usage with better type safety and overload behavior.
*/

#include <cstddef>
#include <iostream>
#include <type_traits>
#include <typeinfo>

using std::cout;
using std::endl;

void section(const char* title) {
    cout << "\n=== " << title << " ===\n";
}

void process(int n) {
    cout << "process(int): " << n << endl;
}

void process(const char* text) {
    cout << "process(const char*): " << (text ? text : "nullptr") << endl;
}

void accepts_nullptr(std::nullptr_t) {
    cout << "accepts_nullptr(std::nullptr_t) called" << endl;
}

int main() {
    section("1) Overload resolution");

    process(0);         // int overload
    process(nullptr);   // pointer overload (unambiguous)
    // process(NULL);   // may be ambiguous depending on NULL definition

    section("2) nullptr has its own type");

    cout << "typeid(nullptr).name() = " << typeid(nullptr).name() << endl;
    static_assert(std::is_same<decltype(nullptr), std::nullptr_t>::value,
                  "nullptr must be std::nullptr_t");

    section("3) Conversions");

    int* ip = nullptr;
    double* dp = nullptr;
    void* vp = nullptr;

    cout << "ip == nullptr ? " << (ip == nullptr ? "true" : "false") << endl;
    cout << "dp == nullptr ? " << (dp == nullptr ? "true" : "false") << endl;
    cout << "vp == nullptr ? " << (vp == nullptr ? "true" : "false") << endl;

    // nullptr is convertible to bool (false), but not to arbitrary integers.
    // bool b = nullptr;
    // cout << "bool(nullptr) = " << (b ? "true" : "false") << endl;
    // int n = nullptr;  // compile error: not implicitly convertible to int

    section("4) std::nullptr_t in APIs");

    accepts_nullptr(nullptr);

    section("Summary");
    cout << "Use nullptr for null pointers in modern C++ code.\n";
    cout << "It improves readability, type safety, and overload selection.\n";

    return 0;
}