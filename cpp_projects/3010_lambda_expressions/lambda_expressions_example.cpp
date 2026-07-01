/*
Lambda Expressions in C++11
===========================
Lambdas are unnamed function objects created inline.
They are especially useful with STL algorithms and short custom behavior.

General form:
  [capture](params) -> return_type { body }
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

void section(const char* title) {
    cout << "\n=== " << title << " ===\n";
}

int main() {
    section("1) Basic syntax and type");

    // A simple lambda that adds two integers.
    auto add = [](int a, int b) { return a + b; };
    cout << "add(2, 3) = " << add(2, 3) << endl;

    // Each lambda has a unique closure type.
    // The type of 'add' is not a function pointer, but a unique class with operator().
    auto add2 = [](int a, int b) { return a + b; };
    cout << "add2(4, 5) = " << add2(4, 5) << endl;

    section("2) Captures by value and by reference");

    int factor = 10;
    // Capture 'factor' by value and by reference.
    auto by_value = [factor](int x) { return x * factor; };
    auto by_ref = [&factor](int x) { return x * factor; };

    cout << "factor initially = " << factor << endl;
    cout << "by_value(3) = " << by_value(3) << endl;
    cout << "by_ref(3) = " << by_ref(3) << endl;

    factor = 20;
    cout << "factor changed to " << factor << endl;
    cout << "by_value(3) still uses old captured value -> " << by_value(3) << endl;
    cout << "by_ref(3) sees new value -> " << by_ref(3) << endl;

    section("3) mutable lambda");

    int counter = 0;
    // A mutable lambda allows modification of captured variables by value.
    // The captured 'counter' is a copy, so changes do not affect the original.
    // Note: mutable is only meaningful for value captures; reference captures can always be modified.
    auto increment_local_copy = [counter]() mutable {
        ++counter;
        return counter;
    };

    cout << "increment_local_copy() = " << increment_local_copy() << endl;
    cout << "increment_local_copy() = " << increment_local_copy() << endl;
    cout << "outside counter remains = " << counter << endl;

    section("4) Lambdas with STL algorithms");

    // Use a lambda to filter and transform a vector of integers.
    std::vector<int> values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    values.push_back(4);
    values.push_back(5);

    int sum = 0;
    // Use std::for_each with a lambda to accumulate the sum of values.
    // Capture 'sum' by reference to modify it inside the lambda.
    // Note: std::for_each is a simple example; in real code, consider using std::accumulate for summation.
    std::for_each(values.begin(), values.end(), [&sum](int v) { sum += v; });
    cout << "sum = " << sum << endl;

    // Use std::find_if with a lambda to find the first even number.
    // The lambda captures nothing and checks if a number is even.
    // Note: std::find_if returns an iterator to the first element satisfying the condition, or end() if none found.
    std::vector<int>::iterator first_even = std::find_if(
        values.begin(), values.end(),
        [](int v) { return v % 2 == 0; }
    );

    if (first_even != values.end()) {
        cout << "first even value = " << *first_even << endl;
    }

    // Use std::sort with a lambda to sort the vector in descending order.
    // The lambda captures nothing and compares two integers.
    std::sort(values.begin(), values.end(), [](int a, int b) { return a > b; });
    cout << "sorted descending: ";
    for (std::size_t i = 0; i < values.size(); ++i) {
        cout << values[i] << ' ';
    }
    cout << endl;

    section("5) Storing lambdas");

    // std::function can store callable objects with matching signature.
    // Note: std::function has some overhead compared to direct lambda usage.
    std::function<bool(const std::string&)> long_enough = [](const std::string& s) {
        return s.size() >= 5;
    };

    cout << "long_enough(\"cat\") = " << (long_enough("cat") ? "true" : "false") << endl;
    cout << "long_enough(\"tiger\") = " << (long_enough("tiger") ? "true" : "false") << endl;

    section("6) Practical guidance");
    cout << "Capture only what you need.\n";
    cout << "Prefer explicit capture lists in teaching and production code.\n";
    cout << "Use reference capture only when object lifetime is guaranteed.\n";

    return 0;
}