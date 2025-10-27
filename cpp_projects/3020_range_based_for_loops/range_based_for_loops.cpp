/*
    Range-based For Loops Example in C++

    Purpose:
    Range-based for loops, introduced in C++11, provide a concise and readable way 
    to iterate over elements in containers such as arrays, vectors, lists, 
    and other standard library collections. They eliminate the need for manual indexing
    and make code easier to write and maintain.

    This example demonstrates how to use range-based for loops to iterate over a vector, 
    modify elements, and work with both value and reference types.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
    // Example 1: Iterating over a vector of integers
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "Numbers: ";
    for (int n : numbers) { // n is a copy of each element
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Example 2: Modifying elements using reference
    for (int& n : numbers) { // n is a reference to each element
        n *= 2; // Double each number
    }

    std::cout << "Numbers after doubling: ";
    for (const int& n : numbers) { // Use const reference to avoid copying
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Example 3: Iterating over a vector of strings
    std::vector<std::string> fruits = {"apple", "banana", "cherry"};
    std::cout << "Fruits: ";
    for (const std::string& fruit : fruits) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;

    // Example 4: Using auto for type deduction
    // The advantage of using 'auto' is that it makes the code more concise and easier 
    // to read, but it can also make it less clear what the actual type is, 
    // which may lead to confusion in complex scenarios. 
    // Therefore, it's important to use 'auto' judiciously and ensure that the code 
    // remains understandable.
    // With respect to the range-based for loop, 'auto' can be particularly useful
    // when iterating over containers with complex or verbose types.
    // With respect to performance, using 'auto' itself does not have a direct impact.
    // However, when combined with references (e.g., 'auto&'), it can help
    // avoid unnecessary copies, thus improving performance.
    // Conversely, using 'auto' without references may lead to copies being made,
    // which could have performance implications for large or complex types.
    // Therefore, it's important to consider the context and the types involved
    // when deciding whether to use 'auto' with or without references in range-based 
    // for loops to balance code clarity and performance. 
    std::cout << "Fruits in uppercase: ";
    for (auto& fruit : fruits) {
        for (size_t i = 0; i < fruit.size(); ++i) { 
            // Convert each character to uppercase
            fruit[i] = toupper(fruit[i]);
        }
        std::cout << fruit << " ";
    }
    std::cout << std::endl;

    return 0;
}