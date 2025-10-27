/*
    Lambda Expressions Example in C++

    Purpose:
    Lambda expressions, introduced in C++11, allow you to define anonymous functions (functions without a name)
    directly in your code. They are useful for short, inline operations, especially as arguments to algorithms,
    event handlers, or for capturing local variables in a concise way.

    This example demonstrates basic lambda syntax, capturing variables, and using lambdas with standard algorithms.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Basic lambda: no capture, adds two numbers
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    std::cout << "add(2, 3) = " << add(2, 3) << std::endl;

    // Lambda with implicit return type
    auto multiply = [](int a, int b) { return a * b; };
    std::cout << "multiply(4, 5) = " << multiply(4, 5) << std::endl;

    // Lambda capturing local variables by value
    int factor = 10;
    auto times_factor = [factor](int x) { return x * factor; };
    std::cout << "times_factor(7) = " << times_factor(7) << std::endl;

    // Lambda capturing local variables by reference
    int sum = 0;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::for_each(numbers.begin(), numbers.end(), [&sum](int x) {
        // Accumulate sum by reference
        sum += x;
    });
    std::cout << "Sum of numbers = " << sum << std::endl;

    // Lambda used directly in std::for_each to print elements
    std::cout << "Numbers: ";
    std::for_each(numbers.begin(), numbers.end(), [](int x) { 
        // Print each number
        std::cout << x << " ";
    });
    std::cout << std::endl;

    // Lambda with mutable capture
    int counter = 0;
    auto increment = [counter]() mutable {
        return ++counter;
    };

    std::cout << "increment() = " << increment() << std::endl; // counter inside lambda is incremented
    std::cout << "increment() = " << increment() << std::endl; // counter inside lambda is incremented again
    std::cout << "counter (outside lambda) = " << counter << std::endl; // counter remains unchanged

    // Lambda as a predicate in std::find_if
    int to_find = 5; // Variable to capture, exists in the vector.
    auto it = std::find_if(numbers.begin(), numbers.end(), [to_find](int x) {
        return x == to_find;
    });

    if (it != numbers.end()) { // Found
        std::cout << "Found " << to_find << " in numbers." << std::endl;
    } else { // Not found
        std::cout << to_find << " not found in numbers." << std::endl;
    }    

    return 0;
}