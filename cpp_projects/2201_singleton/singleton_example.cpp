#include <iostream>

/*
This file demonstrates the Singleton design pattern in C++.

The Singleton pattern ensures that a class has only one instance and provides a global point of access to it.
This is useful when exactly one object is needed to coordinate actions across the system, such as a configuration manager or a logging class.

In this implementation:
    - The constructor is private to prevent direct instantiation.
    - A private static pointer holds the single instance of the class.
    - The copy constructor and assignment operator are deleted to prevent copying.
    - The static getInstance() method provides access to the single instance, creating it if it does not already exist.
    - Example usage in main() demonstrates that multiple calls to getInstance() return the same object.

Note: The double-checked locking in getInstance() is not thread-safe in standard C++.
For thread safety, consider using std::call_once, std::mutex, or function-local static variables (since C++11).
*/

// Singleton class definition
class Singleton {
private:
    // Private static pointer to the single instance
    static Singleton* instance;

    // Private constructor to prevent direct instantiation
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

    // Delete copy constructor and assignment operator to prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // Static method to access the single instance
    static Singleton* getInstance() {
        // Double-checked locking for thread safety
        if (instance == nullptr) {
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }

    // Example method
    void showMessage() {
        std::cout << "Hello from the Singleton!\n";
    }
};

// Initialize static members
Singleton* Singleton::instance = nullptr;

// Example usage
int main() {
    // Get the singleton instance and call a method
    Singleton* s1 = Singleton::getInstance();
    s1->showMessage();

    // Get the singleton instance again (should be the same instance)
    Singleton* s2 = Singleton::getInstance();
    if (s1 == s2) {
        std::cout << "Both pointers point to the same Singleton instance.\n";
    } else {
        std::cout << "Different instances (should not happen).\n";
    }

    return 0;
}