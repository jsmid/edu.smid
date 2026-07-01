#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <typeinfo>
#include <type_traits>

using std::cout;
using std::endl;

// Helper to print a section title.
void section(const char* title) {
    cout << "\n=== " << title << " ===\n";
}

// In C++11 we cannot use std::is_same_v, so we use this helper style.
template <typename A, typename B>
void print_type_match(const char* label) {
    cout << label << ": " << (std::is_same<A, B>::value ? "match" : "different") << "\n";
}

int main() {
    section("1) Basic auto type deduction");

    // Rule: auto deduces from the initializer expression.
    // Think of it as: replace 'auto' with the exact type of the right side,
    // then apply normal deduction adjustments.
    auto i = 42;          // int
    auto d = 3.14;        // double
    auto c = 'A';         // char
    auto ok = true;       // bool

    cout << "i = " << i << "\n";
    cout << "d = " << d << "\n";
    cout << "c = " << c << "\n";
    cout << "ok = " << ok << "\n";

    section("2) auto with containers and iterators");

    std::vector<int> numbers{10, 20, 30, 40};

    // Without auto, iterator types can be long and hard to read.
    // Example of explicit type:
    // std::vector<int>::iterator it = numbers.begin();
    // auto keeps the code shorter and still type-safe.
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    section("3) Top-level const is dropped (copy semantics)");

    const int ci = 100;
    auto a = ci;          // deduced as int (const removed)
    a = 101;              // OK because 'a' is not const

    cout << "ci = " << ci << ", a = " << a << "\n";

    // Why is const dropped here?
    // Plain auto follows template type deduction for by-value parameters.
    // Conceptually, this behaves like calling:
    //   template <typename T> void f(T);
    //   f(ci);
    // For by-value deduction, top-level const is ignored, so T becomes int.
    // This makes sense because 'a' is a new copied object, not an alias to ci.
    //
    // Important distinction:
    // - top-level const (const object itself): dropped for plain auto
    // - low-level const (through pointer/reference target): preserved
    // Example: const int* p; auto q = p;  // q is const int*

    section("4) auto vs auto& (copy vs alias)");

    int x = 5;
    int& refX = x;
    const int& crefX = x;

    // plain auto creates a new variable (usually a copy)
    auto b = refX;        // int (reference removed)
    auto c2 = crefX;      // int (const and reference removed)

    // auto& creates a reference (alias to existing object)
    auto& rb = refX;      // int&
    const auto& rc = crefX; // const int&

    b = 50;               // changes only b
    rb = 60;              // changes x

    cout << "x = " << x << ", b = " << b << ", c2 = " << c2 << "\n";
    cout << "rc = " << rc << "\n";

    // Key idea:
    // - plain auto: own value (copy). Modifying it does not affect original.
    // - auto&: alias. Modifying it changes the original object.
    // - const auto&: read-only alias. No copy, but cannot modify through it.

    section("5) Practical difference in loops");

    std::vector<std::string> names{"Alice", "Bob"};

    // This loop copies each element into a local variable.
    // The original vector remains unchanged.
    for (auto name : names) {
        name += "!";
    }
    cout << "after auto copy loop: ";
    for (const auto& name : names) {
        cout << name << ' ';
    }
    cout << "\n";

    // This loop binds a reference to each original element.
    // Changes are written back to the vector.
    for (auto& name : names) {
        name += "!";
    }
    cout << "after auto& reference loop: ";
    for (const auto& name : names) {
        cout << name << ' ';
    }
    cout << "\n";

    section("6) Pointers and auto");

    int value = 7;
    int* p = &value;
    const int* cp = &value;

    auto p1 = p;          // int*
    auto p2 = cp;         // const int*
    auto* p3 = p;         // int* (explicitly pointer style)

    *p1 = 8;
    cout << "value = " << value << ", *p2 = " << *p2 << ", *p3 = " << *p3 << "\n";

    section("7) auto with brace initialization");

    auto n1 = 7;          // int
    auto n2 = {7};        // std::initializer_list<int>
    auto n3{7};           // int in C++11 direct-list initialization

    cout << "n1 = " << n1 << "\n";
    cout << "n2 has " << n2.size() << " element(s)\n";
    cout << "n3 = " << n3 << "\n";

    // Be careful: list initialization can change deduction results.
    // auto mixed = {1, 2.0}; // error: cannot deduce one initializer_list type

    section("8) Useful pattern: range-based for with auto");

    std::map<std::string, int> scores{
        {"Alice", 90},
        {"Bob", 85},
        {"Carol", 95}
    };

    // const auto& avoids copying each key-value pair.
    for (const auto& entry : scores) {
        cout << entry.first << ": " << entry.second << "\n";
    }

    section("9) auto in function return types (C++11 limitation)");

    // In pure C++11, you cannot write:
    // auto f() { return 123; }   // this is allowed in C++14+
    // C++11 needs trailing return type when using auto in declarations:
    // auto f() -> int { return 123; }
    cout << "C++11 requires trailing return type with auto for functions.\n";

    section("10) Small type checks with std::is_same");

    print_type_match<decltype(i), int>("decltype(i) vs int");
    print_type_match<decltype(a), int>("decltype(a) vs int");
    print_type_match<decltype(rb), int&>("decltype(rb) vs int&");
    print_type_match<decltype(rc), const int&>("decltype(rc) vs const int&");

    section("Summary");
    cout << "auto lets the compiler deduce type from initializer.\n";
    cout << "Use auto when type is obvious or verbose (iterators, lambdas).\n";
    cout << "auto creates a new value; auto& creates an alias to existing value.\n";
    cout << "Plain auto usually creates a copy and may drop top-level const/reference.\n";
    cout << "Prefer auto&, const auto&, or auto* when you need to keep qualifiers.\n";
    cout << "Watch brace-initialization because it can deduce initializer_list.\n";

    // Optional: show runtime type names (implementation-specific strings).
    cout << "\n(typeid examples)\n";
    cout << "type of i : " << typeid(i).name() << "\n";
    cout << "type of d : " << typeid(d).name() << "\n";

    return 0;
}
