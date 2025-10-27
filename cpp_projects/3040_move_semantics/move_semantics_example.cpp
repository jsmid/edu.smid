/*
    Move Semantics and Rvalue References Example in C++

    Purpose:
    Move semantics and rvalue references, introduced in C++11, allow efficient transfer of resources (like dynamic memory)
    from one object to another, avoiding unnecessary deep copies. This is especially useful for classes that manage resources,
    such as containers, strings, or file handles.

    - An lvalue is an object that has a persistent address (can appear on the left side of assignment).
    - An rvalue is a temporary object (like the result of an expression) that can be "moved from".

    The move constructor and move assignment operator use rvalue references (`Type&&`) to "steal" resources from temporaries,
    making code faster and more efficient.

    This example demonstrates a simple class managing a dynamic array, with copy and move semantics.
*/

#include <iostream>
#include <algorithm>

// Buffer class that manages a dynamic array of integers 
// and demonstrates move semantics.
class Buffer {
    int* data;      // Pointer to dynamically allocated array
    size_t size;    // Size of the array
public:
    // Constructor
    Buffer(size_t n) : data(new int[n]), size(n) {
        std::cout << "Constructed Buffer of size " << size << std::endl;
        std::fill(data, data + size, 0); // Initialize with zeros. std::fill is used for initialization.
    }

    // Destructor
    ~Buffer() {
        delete[] data;
        std::cout << "Destroyed Buffer of size " << size << std::endl;
    }

    // Copy constructor (deep copy)
    Buffer(const Buffer& other) : data(new int[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data); // Copy data from other Buffer 
        std::cout << "Copied Buffer of size " << size << std::endl;
    }

    // Move constructor (steals resources)
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Moved Buffer of size " << size << std::endl;
    }

    // Copy assignment
    Buffer& operator=(const Buffer& other) {
        if (this != &other) { // Check for self-assignment
            delete[] data;    // Free existing resource
            size = other.size; // Update size
            data = new int[size]; // Allocate new memory
            std::copy(other.data, other.data + size, data); // Copy data
            std::cout << "Copy-assigned Buffer of size " << size << std::endl;
        }
        return *this; // Return *this to allow chained assignments
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) { // Check for self-assignment
            delete[] data;    // Free existing resource
            // Steal resources from other
            data = other.data; // Take ownership of other's data
            size = other.size; // Update size
            // Leave other in a valid but unspecified state
            other.data = nullptr; // Nullify other's data pointer
            other.size = 0;       // Reset other's size
            std::cout << "Move-assigned Buffer of size " << size << std::endl;
        }
        return *this; // Return *this to allow chained assignments
    }

    void fill(int value) {
        std::fill(data, data + size, value);
    }

    void print() const {
        std::cout << "Buffer data: ";
        for (size_t i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }
};

Buffer createBuffer(size_t n) {
    Buffer buf(n);
    buf.fill(42);
    return buf; // Return by value, triggers move semantics 
}

int main() {
    Buffer a(5);
    a.fill(1);
    a.print();

    Buffer b = a; // Copy constructor
    b.print();

    Buffer c = createBuffer(3); // Move constructor
    c.print();

    Buffer d(2);
    d = createBuffer(4); // Move assignment
    d.print();

    return 0;
}